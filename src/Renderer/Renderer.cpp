#include "Renderer.h"

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "../Font.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <array>

namespace Aegis {

    static const size_t max_quad_count = 1000;
    static const size_t max_vertex_count = max_quad_count * 4;
    static const size_t max_index_count = max_quad_count * 6;
    static const size_t max_textures = 32;

    static std::unique_ptr<Shader> shader_;
    static std::unique_ptr<Shader> font_shader_;
    static std::unique_ptr<VertexArray> vertex_array_;
    static glm::mat4 projection_;
    static std::unique_ptr<Texture> white_texture_;
    static std::unique_ptr<Font> default_font_;

    struct Vertex
    {
        glm::vec3 position_;
        glm::vec4 color_;
        glm::vec2 tex_coords_;
        float texture_ID_;
    };

    struct RenderData
    {
        GLuint quad_VA_ = 0;
        GLuint quad_VB_ = 0;
        GLuint quad_IB_ = 0;

        GLuint white_texture_ = 0;
        uint32_t white_texture_slot_ = 0;

        uint32_t index_count_ = 0;

        Vertex* quad_buffer_ = nullptr;
        Vertex* quad_buffer_ptr_ = nullptr;

        std::array<uint32_t, max_textures> texture_slots_;
        uint32_t texture_slot_index_ = 1;
    };


    static RenderData data_;

    void Renderer2D::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        projection_ = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);

        font_shader_ = std::make_unique<Shader>("assets/shaders/FontShader.glsl");
        font_shader_->Bind();
        font_shader_->SetMat4("u_Projection", projection_);
        font_shader_->SetInt("u_Texture", 0);

        shader_ = std::make_unique<Shader>("assets/shaders/Shader.glsl");
        shader_->Bind();
        shader_->SetMat4("u_Projection", projection_);
        shader_->SetInt("u_Texture", 0);

        vertex_array_ = std::make_unique<VertexArray>();
        white_texture_ = std::make_unique<Texture>();
        default_font_ = std::make_unique<Font>("assets/fonts/WorkSans-Regular.ttf", 16);

        data_.quad_buffer_ = new Vertex[max_vertex_count];

        glCreateVertexArrays(1, &data_.quad_VA_);
        glBindVertexArray(data_.quad_VA_);

        glCreateBuffers(1, &data_.quad_VB_);
        glBindBuffer(GL_ARRAY_BUFFER, data_.quad_VB_);
        glBufferData(GL_ARRAY_BUFFER, max_vertex_count * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexArrayAttrib(data_.quad_VA_, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position_));

        glEnableVertexArrayAttrib(data_.quad_VA_, 1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color_));

        glEnableVertexArrayAttrib(data_.quad_VA_, 2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tex_coords_));

        glEnableVertexArrayAttrib(data_.quad_VA_, 3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texture_ID_));

        uint32_t indices[max_index_count];
        uint32_t offset = 0;
        for (int i = 0; i < max_index_count; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

        glCreateBuffers(1, &data_.quad_IB_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_.quad_IB_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glCreateTextures(GL_TEXTURE_2D, 1, &data_.white_texture_);
        glBindTexture(GL_TEXTURE_2D, data_.white_texture_);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uint32_t color = 0xffffffff;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

        data_.texture_slots_[0] = data_.white_texture_;
        for (size_t i = 1; i < max_textures; ++i) {
            data_.texture_slots_[i] = 0;
        }
    }

    void Renderer2D::Shutdown()
    {
        glDeleteVertexArrays(1, &data_.quad_VA_);
        glDeleteBuffers(1, &data_.quad_IB_);
        glDeleteBuffers(1, &data_.quad_VB_);
        glDeleteTextures(1, &data_.white_texture_);

        delete[] data_.quad_buffer_;
    }

	void Renderer2D::BeginBatch()
	{
        data_.quad_buffer_ptr_ = data_.quad_buffer_;
	}

	void Renderer2D::EndBatch()
	{
        shader_->Bind();
        GLsizeiptr size = (uint8_t*)data_.quad_buffer_ptr_ - (uint8_t*)data_.quad_buffer_;
        glBindBuffer(GL_ARRAY_BUFFER, data_.quad_VB_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data_.quad_buffer_);

        for (uint32_t i = 0; i < data_.texture_slot_index_; ++i) {
            glBindTextureUnit(i, data_.texture_slots_[i]);
        }

        glBindVertexArray(data_.quad_VA_);
        glDrawElements(GL_TRIANGLES, data_.index_count_, GL_UNSIGNED_INT, nullptr);
        data_.index_count_ = 0;
        data_.texture_slot_index_ = 1;
	}

    void Renderer2D::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
        shader_->Bind();
        //shader_->SetMat4("u_Transform", glm::mat4(1.0));
        if (data_.index_count_ >= max_index_count) {
            EndBatch();
            BeginBatch();
        }

        float texture_index = 0.0f;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f }) * glm::scale(glm::mat4(1.0), { size.x, size.y, 1.0 });
        glm::vec4 vertex1_pos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex1_pos.x, vertex1_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = {0.0f, 0.0f};
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        glm::vec4 vertex2_pos = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex2_pos.x, vertex2_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { 1.0f, 0.0f };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        glm::vec4 vertex3_pos = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex3_pos.x, vertex3_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { 1.0f, 1.0f };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        glm::vec4 vertex4_pos = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex4_pos.x, vertex4_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { 0.0f, 1.0f };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;
        
        data_.index_count_ += 6;
	}

    void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const std::unique_ptr<Texture>& texture)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f }) * glm::scale(glm::mat4(1.0), { size.x, size.y, 1.0 });
        shader_->Bind();
        shader_->SetMat4("u_Transform", transform);
        shader_->SetFloat4("u_Color", glm::vec4(1.0f));
        texture->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    void Renderer2D::DrawText(const std::string& text, const glm::vec2& pos, const glm::vec4& color)
    {
        font_shader_->Bind();
        font_shader_->SetFloat4("u_Color", color);
        vertex_array_->Bind();
        
        auto pen_pos = pos;
        pen_pos.y += default_font_->tallest_glyph_height_;
        for (const auto& c : text) {
            auto glyph = default_font_->glyphs_[c];
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pen_pos.x + glyph.bearing_x, pen_pos.y - glyph.bearing_y, 0.0f }) * glm::scale(glm::mat4(1.0), { glyph.width, glyph.height, 1.0 });
            font_shader_->SetMat4("u_Transform", transform);
            glyph.texture.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            pen_pos.x += glyph.advance >> 6;
        }
    }
}
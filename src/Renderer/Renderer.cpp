#include "Renderer.h"

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "../Font.h"
#include "../Assert.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <array>
#include <iostream>

namespace Aegis {

    static const size_t max_textures = 32;
    static std::unique_ptr<Shader> shader_;
    static std::unique_ptr<VertexArray> vertex_array_;
    static glm::mat4 projection_;
    static std::shared_ptr<Font> default_font_;
    static std::shared_ptr<Texture> white_texture_;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> cached_text_;

    struct RenderData
    {
        uint32_t index_count_ = 0;

        VertexArray::Vertex* quad_buffer_ = nullptr;
        VertexArray::Vertex* quad_buffer_ptr_ = nullptr;

        std::array<uint32_t, max_textures> texture_slots_;
        uint32_t texture_slot_index_ = 1;
    };

    static RenderData data_;

    void Renderer2D::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearDepth(1.0f);

        int samplers[max_textures];
        for (int i = 0; i < max_textures; ++i) {
            samplers[i] = i;
        }

        //default shaders are hardcoded in Shader.h
        shader_ = std::make_unique<Shader>(default_vertex_shader, default_fragment_shader);
        shader_->Bind();
        shader_->SetMat4("u_Projection", projection_);
        shader_->SetIntVector("u_Textures", max_textures, samplers);

        //1x1 square texture for colored quads.
        unsigned char white_data[4] = { 255, 255, 255, 255 };
        white_texture_ = Texture::Create(white_data, 1, 1, 4);

        vertex_array_ = std::make_unique<VertexArray>();
        data_.quad_buffer_ = new VertexArray::Vertex[vertex_array_->max_vertex_count_];
       
        data_.texture_slots_[0] = white_texture_->ID_;
        for (size_t i = 1; i < max_textures; ++i) {
            data_.texture_slots_[i] = 0;
        }
    }

    void Renderer2D::Shutdown()
    {
        delete[] data_.quad_buffer_;
    }

    void Renderer2D::BeginScene(const glm::mat4& camera_projection)
	{
        projection_ = camera_projection;

        shader_->Bind();
        shader_->SetMat4("u_Projection", projection_);

        data_.quad_buffer_ptr_ = data_.quad_buffer_;
	}

	void Renderer2D::EndScene()
	{
        GLsizeiptr size = (uint8_t*)data_.quad_buffer_ptr_ - (uint8_t*)data_.quad_buffer_;
        glBindBuffer(GL_ARRAY_BUFFER, vertex_array_->vertex_buffer_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data_.quad_buffer_);

        for (uint32_t i = 0; i < data_.texture_slot_index_; ++i) {
            glBindTextureUnit(i, data_.texture_slots_[i]);
        }

        glBindVertexArray(vertex_array_->ID_);
        glDrawElements(GL_TRIANGLES, data_.index_count_, GL_UNSIGNED_INT, nullptr);
        data_.index_count_ = 0;
        data_.texture_slot_index_ = 1;
	}

    void Renderer2D::SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    Font& Renderer2D::GetFont()
    {
        return *default_font_;
    }

    void RendererClear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color, const float z_idx)
	{
        DrawQuad(pos, size, white_texture_->ID_, color, z_idx);
	}

    void DrawQuad(const Vec2& pos, const Texture& texture, const float z_idx, const Vec4& color)
    {
        DrawQuad(pos, texture.size_, texture, z_idx, color);
    }

    void DrawQuad(const Vec2& pos, const Vec2& size, const Texture& texture, const float z_idx, const Vec4& color)
    {
        DrawQuad(pos, size, texture.ID_, color, z_idx, { 0.0f, 0.0f, 1.0f, 1.0f });
    }

    void DrawQuad(const Vec2& pos, const Vec2& size, unsigned int texture_id, const Vec4& color, const float z_idx, const Vec4& tex_coords, const float rotation, bool h_flip)
    {
        if (data_.index_count_ >= vertex_array_->max_index_count_ || data_.texture_slot_index_ > 31) {
            Renderer2D::EndScene();
            Renderer2D::BeginScene(projection_);
        }

        float texture_index = 0.0f;
        for (uint32_t i = 1; i < data_.texture_slot_index_; ++i) {
            if (data_.texture_slots_[i] == texture_id) {
                texture_index = (float)i;
                break;
            }
        }
        if (texture_index == 0.0f) {
            texture_index = (float)data_.texture_slot_index_;
            data_.texture_slots_[data_.texture_slot_index_] = texture_id;
            data_.texture_slot_index_++;
        }

        AE_ASSERT(data_.quad_buffer_ptr_ != nullptr, "Must Call BeginScence() before drawing\n");

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(pos.x, pos.y , 0.0f));

        //move origin to center to rotate properly
        transform = glm::translate(transform, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));


        glm::vec4 vertex1_pos;
        glm::vec4 vertex2_pos;
        glm::vec4 vertex3_pos;
        glm::vec4 vertex4_pos;
        if (h_flip) {
            vertex2_pos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            vertex1_pos = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); 
            vertex4_pos = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
            vertex3_pos = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else {
            vertex1_pos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            vertex2_pos = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            vertex3_pos = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
            vertex4_pos = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        }

        data_.quad_buffer_ptr_->position_ = { vertex1_pos.x, vertex1_pos.y, vertex1_pos.z };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.x, tex_coords.y };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        data_.quad_buffer_ptr_->position_ = { vertex2_pos.x, vertex2_pos.y, vertex2_pos.z };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.z, tex_coords.y };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        data_.quad_buffer_ptr_->position_ = { vertex3_pos.x, vertex3_pos.y, vertex3_pos.z };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.z, tex_coords.w };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        data_.quad_buffer_ptr_->position_ = { vertex4_pos.x, vertex4_pos.y, vertex4_pos.z };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.x, tex_coords.w };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        data_.index_count_ += 6;
    }
    void DrawStaticText(const std::string& text, const Vec2& pos, const Vec4& color, const float z_idx)
    {
        //if already cached
	    std::string index = text + default_font_->font_name_ + std::to_string(default_font_->size_);
        if (cached_text_.count(index)) {
            DrawQuad(pos, *cached_text_[index], z_idx, color);
        }
        //create texture and cache
        else{
            auto texture = Texture::CreateFromText(text, *default_font_);
            
            DrawQuad(pos, *texture, z_idx, color);
            cached_text_[index] = texture;
        }
    }
    void DrawText(const std::string& text, const Vec2& pos, const Vec4& color, const float z_idx)
    {
        Vec2 pen_pos = pos;
        pen_pos.y += default_font_->tallest_glyph_height_;

        for (const auto& c : text) {

            auto glyph = default_font_->glyphs_[c];
            DrawQuad({ pen_pos.x + glyph.bearing.x, pen_pos.y - glyph.bearing.y }, glyph.size, default_font_->atlas_->ID_, color, z_idx, glyph.texture_coords_);
            pen_pos.x += glyph.advance;
        }
    }
    void RenderSprite(const Vec2& pos, const Sprite& sprite)
    {
        DrawQuad(pos, sprite.GetSubTextureRect().size * sprite.scale_, sprite.texture_->ID_, sprite.color_, 0, sprite.GetTextureCoords(), sprite.rotation_, sprite.horizontal_flip);
    }
    void Renderer2D::SetFont(std::shared_ptr<Font> font)
    {
        default_font_ = font;
    }
    void Renderer2D::SetProjection(const glm::mat4& projection)
    {
        EndScene();
        BeginScene(projection);
    }
}

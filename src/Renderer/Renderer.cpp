#include "Renderer.h"

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "../Font.h"

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
    static std::unique_ptr<Texture> white_texture_;
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
        unsigned char white_data[4] = { 225, 225, 225, 225 };
        white_texture_ = std::make_unique<Texture>(white_data, 1, 1, 4);

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
		glClear(GL_COLOR_BUFFER_BIT);
	}

    void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color)
	{
        if (data_.index_count_ >= vertex_array_->max_index_count_) {
            Renderer2D::EndScene();
            Renderer2D::BeginScene(projection_);
        } 

        DrawQuad(pos, size, 0, color);
	}

    void DrawQuad(const Vec2& pos, const std::shared_ptr<Texture>& texture, const Vec4& color)
    {
        DrawQuad(pos, texture->size_, texture,  color);
    }

    void DrawQuad(const Vec2& pos, const Vec2& size, const std::shared_ptr<Texture>& texture, const Vec4& color)
    {
        if (data_.index_count_ >= vertex_array_->max_index_count_ || data_.texture_slot_index_ > 31) {
            Renderer2D::EndScene();
            Renderer2D::BeginScene(projection_);
        }

        float texture_index = 0.0f;
        for (uint32_t i = 1; i < data_.texture_slot_index_; ++i) {
            if (data_.texture_slots_[i] == texture->ID_) {
                texture_index = (float)i;
                break;
            }
        }
        if (texture_index == 0.0f) {
            texture_index = (float)data_.texture_slot_index_;
            data_.texture_slots_[data_.texture_slot_index_] = texture->ID_;
            data_.texture_slot_index_++;
        }

        DrawQuad(pos, size, texture_index, color, texture->tex_coords_);
    }

    void DrawQuad(const Vec2& pos, const Vec2& size, const float texture_index, const Vec4& color, const Vec4& tex_coords)
    {

        if (data_.quad_buffer_ptr_ == nullptr) {
            std::cout << "Must Call BeginScene() before drawing\n";
        }
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f }) * glm::scale(glm::mat4(1.0), { size.x, size.y, 1.0 });

        glm::vec4 vertex1_pos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex1_pos.x, vertex1_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.x, tex_coords.y };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        glm::vec4 vertex2_pos = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex2_pos.x, vertex2_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.z, tex_coords.y };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        glm::vec4 vertex3_pos = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex3_pos.x, vertex3_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.z, tex_coords.w };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        glm::vec4 vertex4_pos = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        data_.quad_buffer_ptr_->position_ = { vertex4_pos.x, vertex4_pos.y, 0.0f };
        data_.quad_buffer_ptr_->color_ = color;
        data_.quad_buffer_ptr_->tex_coords_ = { tex_coords.x, tex_coords.w };
        data_.quad_buffer_ptr_->texture_ID_ = texture_index;
        data_.quad_buffer_ptr_++;

        data_.index_count_ += 6;
    }
    void DrawStaticText(const std::string& text, const Vec2& pos, const Vec4& color)
    {
        //if already cached
	    std::string index = text + default_font_->font_name_ + std::to_string(default_font_->size_);
        if (cached_text_.count(index)) {
            DrawQuad(pos, cached_text_[index], color);
        }
        //create texture and cache
        else{
            auto texture = Texture::TextureFromText(text, default_font_);
            
            DrawQuad(pos, texture, color);
            cached_text_[index] = texture;
        }
    }
    void DrawText(const std::string& text, const Vec2& pos, const Vec4& color)
    {
        Vec2 pen_pos = pos;
        pen_pos.y += default_font_->tallest_glyph_height_;

        for (const auto& c : text) {

            auto glyph = default_font_->glyphs_[c];
            DrawQuad({ pen_pos.x + glyph.bearing.x, pen_pos.y - glyph.bearing.y }, glyph.texture_, color);
            pen_pos.x += glyph.advance;
        }
    }
    void RenderSprite(const Sprite& sprite)
    {
        DrawQuad(sprite.rect_.pos, sprite.texture_);
    }
    void Renderer2D::SetFont(const std::shared_ptr<Font>& font)
    {
        default_font_ = font;
    }
    void Renderer2D::SetProjection(const glm::mat4& projection)
    {
        EndScene();
        BeginScene(projection);
    }
}

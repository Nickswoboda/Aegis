#include "Renderer.h"

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "Font.h"
#include "../Core/Assert.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <array>
#include <iostream>

namespace Aegis {

    static std::shared_ptr<Font> s_default_font;
    static std::shared_ptr<Texture> s_white_texture;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> s_cached_text;

    struct RenderData
    {
        std::unique_ptr<Shader> shader_;
        Mat4 projection_;

        uint32_t index_count_ = 0;

        std::unique_ptr<VertexArray> vertex_array_;
        VertexArray::Vertex* quad_buffer_ = nullptr;
        VertexArray::Vertex* quad_buffer_ptr_ = nullptr;

        static const size_t max_textures_ = 32;
        std::array<uint32_t, max_textures_> texture_slots_{};
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

        int samplers[data_.max_textures_];
        for (int i = 0; i < data_.max_textures_; ++i) {
            samplers[i] = i;
        }

        //default shaders are hardcoded in Shader.h
        data_.shader_ = std::make_unique<Shader>(default_vertex_shader, default_fragment_shader);
        data_.shader_->Bind();
        data_.shader_->SetMat4("u_Projection", data_.projection_);
        data_.shader_->SetIntVector("u_Textures", data_.max_textures_, samplers);

        //1x1 square texture for colored quads.
        unsigned char white_data[4] = { 255, 255, 255, 255 };
        s_white_texture = Texture::Create(white_data, 1, 1, 4);

        data_.vertex_array_ = std::make_unique<VertexArray>();
        data_.quad_buffer_ = new VertexArray::Vertex[data_.vertex_array_->max_vertex_count_];
       
        data_.texture_slots_[0] = s_white_texture->ID_;
    }

    void Renderer2D::Shutdown()
    {
        delete[] data_.quad_buffer_;
    }

    void Renderer2D::BeginScene(const Mat4& camera_projection)
	{
        data_.projection_ = camera_projection;

        data_.shader_->Bind();
        data_.shader_->SetMat4("u_Projection", data_.projection_);

        data_.quad_buffer_ptr_ = data_.quad_buffer_;
	}

	void Renderer2D::EndScene()
	{
        GLsizeiptr size = (uint8_t*)data_.quad_buffer_ptr_ - (uint8_t*)data_.quad_buffer_;
        glBindBuffer(GL_ARRAY_BUFFER, data_.vertex_array_->vertex_buffer_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data_.quad_buffer_);

        for (uint32_t i = 0; i < data_.texture_slot_index_; ++i) {
            glBindTextureUnit(i, data_.texture_slots_[i]);
        }

        data_.vertex_array_->Bind();
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
        return *s_default_font;
    }

    void RendererClear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color, const float z_idx)
	{
        DrawQuad(pos, size, *s_white_texture, color, z_idx);
	}

    void DrawQuad(const Vec2& pos, const Texture& texture, const Vec4& color, const float z_idx)
    {
        DrawQuad(pos, texture.size_, texture, color, z_idx);
    }

    void DrawQuad(const Vec2& pos, const Vec2& size, const Texture& texture, const Vec4& color, const float z_idx)
    {
		auto transform = Mat4::Identity;
		transform.Translate(pos);
		transform.Scale(size);
        DrawQuad(transform, texture.ID_, { 0.0f, 0.0f, 1.0f, 1.0f }, color);
    }

	void DrawSubTexture(const Vec2& pos, const Vec2& size, const Texture& texture, const Vec4& tex_coords)
	{
		auto transform = Mat4::Identity;
		transform.Translate(pos);
		transform.Scale(size);
        DrawQuad(transform, texture.ID_, tex_coords, {1.0f, 1.0f, 1.0f, 1.0f});
	}

    void DrawQuad(const Mat4& transform, unsigned int texture_id, const Vec4& tex_coords, const Vec4& color)
    {
        AE_ASSERT(data_.quad_buffer_ptr_ != nullptr, "Must Call BeginScence() before drawing\n");

        if (data_.index_count_ >= data_.vertex_array_->max_index_count_ || data_.texture_slot_index_ > 31) {
            Renderer2D::EndScene();
            Renderer2D::BeginScene(data_.projection_);
        }

        float texture_index = -1.0f;
        for (uint32_t i = 0; i < data_.texture_slot_index_; ++i) {
            if (data_.texture_slots_[i] == texture_id) {
                texture_index = (float)i;
                break;
            }
        }
        if (texture_index == -1.0f) {
            texture_index = (float)data_.texture_slot_index_;
            data_.texture_slots_[data_.texture_slot_index_] = texture_id;
            data_.texture_slot_index_++;
        }

        Vec2 texture_coords[4] = { {tex_coords.x, tex_coords.y}, 
                                   {tex_coords.z, tex_coords.y}, 
                                   {tex_coords.z, tex_coords.w}, 
                                   {tex_coords.x, tex_coords.w} };

        for (int i = 0; i < 4; ++i) {
            Vec4 vertex_pos = data_.vertex_array_->vertex_positions_[i] * transform;
            data_.quad_buffer_ptr_->position_ = Aegis::Vec3(static_cast<int>(vertex_pos.x), static_cast<int>(vertex_pos.y), vertex_pos.z );
            data_.quad_buffer_ptr_->color_ = color;
            data_.quad_buffer_ptr_->tex_coords_ = texture_coords[i];
            data_.quad_buffer_ptr_->texture_ID_ = texture_index;
            data_.quad_buffer_ptr_++;
        }

        data_.index_count_ += 6;
    }
    void DrawStaticText(const std::string& text, const Vec2& pos, const Vec4& color, const float z_idx)
    {
        //if already cached
	    std::string index = text + s_default_font->font_name_ + std::to_string(s_default_font->size_);
        if (s_cached_text.count(index)) {
            DrawQuad(pos, *s_cached_text[index], color, z_idx);
        }
        //create texture and cache
        else{
            auto texture = Texture::CreateFromText(text, *s_default_font);
            
            DrawQuad(pos, *texture, color, z_idx);
            s_cached_text[index] = texture;
        }
    }
    void DrawText(const std::string& text, const Vec2& pos, const Vec4& color, const float z_idx)
    {
        Vec2 pen_pos = pos;
        pen_pos.y += s_default_font->highest_glyph_bearing_;

        for (const auto& c : text) {

            const auto& glyph = s_default_font->glyphs_[c];

			auto transform = Mat4::Identity;
			transform.Translate({pen_pos.x + glyph.bearing.x, pen_pos.y - glyph.bearing.y});
			transform.Scale( {glyph.size.x, glyph.size.y} );

            DrawQuad(transform, s_default_font->atlas_->ID_, glyph.texture_coords_,color);
            pen_pos.x += glyph.advance;
        }
    }

    void Renderer2D::SetFont(std::shared_ptr<Font> font)
    {
        s_default_font = font;
    }
    void Renderer2D::SetProjection(const Mat4& projection)
    {
        EndScene();
        BeginScene(projection);
    }
}

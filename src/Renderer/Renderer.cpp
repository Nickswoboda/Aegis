#include "Renderer.h"

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "../Font.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace Aegis {

    static std::unique_ptr<Shader> shader_;
    static std::unique_ptr<Shader> font_shader_;
    static std::unique_ptr<VertexArray> vertex_array_;
    static glm::mat4 projection_;
    static std::unique_ptr<Texture> white_texture_;
    static std::unique_ptr<Font> default_font_;


    void Renderer2D::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        font_shader_ = std::make_unique<Shader>("assets/shaders/FontShader.glsl");
        shader_ = std::make_unique<Shader>("assets/shaders/Shader.glsl");

        vertex_array_ = std::make_unique<VertexArray>();
        projection_ = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
        shader_->Bind();
        shader_->SetMat4("u_Projection", projection_);
        shader_->SetInt("u_Texture", 0);
        font_shader_->Bind();
        font_shader_->SetMat4("u_Projection", projection_);
        font_shader_->SetInt("u_Texture", 0);
        white_texture_ = std::make_unique<Texture>();

        default_font_ = std::make_unique<Font>("assets/fonts/WorkSans-Regular.ttf", 48);
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
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f }) * glm::scale(glm::mat4(1.0), { size.x, size.y, 1.0 });
        shader_->Bind();
        shader_->SetMat4("u_Transform", transform);
        shader_->SetFloat4("u_Color", color);
        white_texture_->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
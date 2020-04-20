#pragma once

#include "Texture.h"
#include "../Font.h"
#include "../Math/Vec2.h"
#include "../Math/Vec4.h"
#include "../Math/Color.h"
#include <glm/glm.hpp>
#include "../Sprite.h"

#include <string>
#include <memory>
namespace Aegis {
	
	class Renderer2D
	{
	public:
		static void Init(int width, int height);
		static void Shutdown();

		static void BeginScene(const glm::mat4& camera_projection);
		static void EndScene();

		static void SetClearColor(float r, float g, float b, float a);
		static void SetDefaultFont(std::shared_ptr<Font>& font);
		static void SetProjection(const glm::mat4& projection);
	};

	void RendererClear();
	void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color);
	void DrawQuad(const Vec2& pos, const Vec2& size, const std::shared_ptr<Texture>& texture, const Vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const Vec4& tex_coords = { 0.0f, 0.0f, 1.0f, 1.0f });
	void DrawQuad(const Vec2& pos, const Vec2& size, const float texture_index, const Vec4& color, const Vec4& tex_coords = { 0.0f, 0.0f, 1.0f, 1.0f });
	void DrawText(const std::string& text, const Vec2& size, const Vec4& color);
	void RenderSprite(const Sprite& sprite);
}
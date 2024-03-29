#pragma once

#include "Texture.h"
#include "Font.h"
#include "Sprite.h"

#include "../Math/Vec2.h"
#include "../Math/Vec4.h"
#include "../Math/Color.h"
#include "../Math/Mat4.h"
#include "../Math/AABB.h"

#include <string>
#include <memory>
namespace Aegis {
	
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Mat4& camera_projection);
		static void EndScene();

		static void SetClearColor(float r, float g, float b, float a);
		static void SetFont(const std::shared_ptr<Font> font);
		static void SetProjection(const Mat4& projection);

		static Font& GetFont();

	};

	void RendererClear();

	void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f}, const float z_idx = 0);
	void DrawQuad(const Vec2& pos, const Vec2& size, const Color& color = {225, 225, 225, 225}, const float z_idx = 0);
	void DrawQuad(const AABB& quad, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f}, const float z_idx = 0);
	void DrawQuad(const AABB& quad, const Color& color = {225, 225, 225, 225}, const float z_idx = 0);

	void DrawSubTexture(const Vec2& pos, const Vec2& size, const Texture& texture, const Vec4& tex_coords);
	void DrawQuad(const Vec2& pos, const Texture& texture, const Vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const float z_idx = 0);
	void DrawQuad(const Vec2& pos, const Vec2& size, const Texture& texture, const Vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const float z_idx = 0);

	void DrawQuad(const Mat4& transform, unsigned int texture_id, const Vec4& tex_coords, const Vec4& color);

	void DrawStaticText(const std::string& text, const Vec2& pos, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f}, const float z_idx = 0);
	void DrawText(const std::string& text, const Vec2& pos, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f}, const float z_idx = 0);
}

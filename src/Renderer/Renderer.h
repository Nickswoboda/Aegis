#pragma once

#include "Texture.h"
#include "../Font.h"
#include "../Math.h"

#include <string>
#include <memory>
namespace Aegis {
	
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginBatch();
		static void EndBatch();

		static void SetClearColor(float r, float g, float b, float a);
		static void SetDefaultFont(std::shared_ptr<Font>& font);
		static void SetProjection(int width, int height);
	};

	void RendererClear();
	void DrawQuad(const Vec2& pos, const Vec2& size, const Vec4& color);
	void DrawQuad(const Vec2& pos, const Vec2& size, const std::unique_ptr<Texture>& texture, const Vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	void DrawQuad(const Vec2& pos, const Vec2& size, const float texture_index, const Vec4& color, const Vec4& tex_coords = { 0.0f, 0.0f, 1.0f, 1.0f });
	void DrawText(const std::string& text, const Vec2& size, const Vec4& color);
}
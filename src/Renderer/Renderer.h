#pragma once

#include "Texture.h"

#include <glm/glm.hpp>

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

		static void ShowFontAtlas();
		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const std::unique_ptr<Texture>& texture);
		static void DrawText(const std::string& text, const glm::vec2& pos, const glm::vec4& color);
	};
}
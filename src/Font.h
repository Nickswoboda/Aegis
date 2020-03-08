#pragma once

#include "Renderer/Texture.h"

#include <unordered_map>
#include <memory>
#include <vector>
namespace Aegis {

	struct Glyph
	{
		glm::vec2 atlas_pos;
		glm::vec2 size;
		glm::vec2 bearing;
		int advance;
	};

	class Font {
	public:
		Font(const std::string& path, int size, int num_glyphs = 128);
		Texture CreateTextureAtlas(const FT_Face& face);
		std::vector<Glyph> glyphs_;
		//used to align to top-left corner when rendering
		int tallest_glyph_height_ = 0;
		Texture atlas_;
		int num_glyphs_ = 0;
	};
}
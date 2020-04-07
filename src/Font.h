#pragma once

#include "Renderer/Texture.h"
#include "Math.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#include <unordered_map>
#include <memory>
#include <vector>
namespace Aegis {

	struct Glyph
	{
		Vec2 atlas_pos;
		Vec2 size;
		Vec2 bearing;
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
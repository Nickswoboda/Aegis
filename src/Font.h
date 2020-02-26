#pragma once

#include "Renderer/Texture.h"

#include <unordered_map>
#include <memory>
namespace Aegis {

	struct Glyph
	{
		Texture texture;
		unsigned int width;
		unsigned int height;
		int bearing_x;
		int bearing_y;
		int advance;
	};

	class Font {
	public:
		Font(const std::string& path, int size);

		std::unordered_map<char, Glyph> glyphs_;
		//used to align to top-left corner when rendering
		int tallest_glyph_height_ = 0;
	};
}
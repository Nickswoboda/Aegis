#include "Font.h"

#include "Renderer/Texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

namespace Aegis {
	Font::Font(const std::string& path, int size)
	{
		FT_Library library;
		FT_Face face;

		int error = FT_Init_FreeType(&library);
		if (error) {
			std::cout << "Unable to initialize FreeType.\n";
		}

		error = FT_New_Face(library, path.c_str(), 0, &face);
		if (error){
			std::cout << "Unable to read font.\n";
		}

		error = FT_Set_Pixel_Sizes(face, size, size);
		if (error) {
			std::cout << "Unable to set pixel size.\n";
		}

		for (int i = 0; i < 128; ++i) {

			error = FT_Load_Char(face, i, FT_LOAD_RENDER);
			if (error) {
				std::cout << "Unable to load character.\n";
			}

			auto glyph = face->glyph;
			glyphs_[i] = { Texture(glyph->bitmap), 
							glyph->bitmap.width, 
							glyph->bitmap.rows,
							glyph->bitmap_left,
							glyph->bitmap_top,
							glyph->advance.x};

			if (glyph->bitmap_top > tallest_glyph_height_) {
				tallest_glyph_height_ = glyph->bitmap_top;
			}
		}

		FT_Done_Face(face);
		FT_Done_FreeType(library);
	}
}
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
		if (error == FT_Err_Unknown_File_Format)
		{
			std::cout << "Font format not supported.\n";
		}
		else if (error)
		{
			std::cout << "Unable to read font.\n";
		}

		error = FT_Set_Pixel_Sizes(face, size, size);

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

			if (glyph->bitmap_top > top_border_) {
				top_border_ = glyph->bitmap_top;
			}
			if (top_border_ == 37) {
				std::cout << i;
			}
		}

	}
}
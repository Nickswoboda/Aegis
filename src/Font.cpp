#include "Font.h"
#include "Assert.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <numeric>

namespace Aegis {
	Font::Font(const std::string& path, int size, int num_glyphs)
		: num_glyphs_(num_glyphs)
	{
		FT_Library library;
		FT_Face face;

		

		int error = FT_Init_FreeType(&library);
		AE_ASSERT(error == 0, "Unable to initialize FreeType.");

		error = FT_New_Face(library, path.c_str(), 0, &face);
		AE_ASSERT(error == 0, "Unable to read font.");

		error = FT_Set_Pixel_Sizes(face, size, size);
		AE_ASSERT(error == 0, "Unable to set pixel size");

		atlas_ = CreateTextureAtlas(face);

		FT_Done_Face(face);
		FT_Done_FreeType(library);
	}

	Texture Aegis::Font::CreateTextureAtlas(const FT_Face& face)
	{
		//src https ://gist.github.com/baines/b0f9e4be04ba4e6f56cab82eef5008ff

		int max_dim = (1 + (face->size->metrics.height >> 6))* ceilf(sqrtf(num_glyphs_));
		int tex_width = 1;
		while (tex_width < max_dim) tex_width <<= 1;
		int tex_height = tex_width;
		int tex_pitch = tex_width * 4;

		unsigned char* pixels = new unsigned char[(size_t)tex_height * tex_pitch]();
		int pen_x = 0, pen_y = 0;

		for (int i = 0; i < num_glyphs_; ++i) {
			FT_Load_Char(face, i, FT_LOAD_RENDER);
			FT_Bitmap* bmp = &face->glyph->bitmap;

			if (pen_x + (bmp->width * 4) >= tex_width) {
				pen_x = 0;
				pen_y += ((face->size->metrics.height >> 6) + 1);
			}

			for (int row = 0; row < bmp->rows; ++row) {
				for (int col = 0; col < bmp->width; ++col) {
					int x = pen_x + col;
					int y = pen_y + row;
					pixels[y * tex_pitch + x*4 + 0] = 225;
					pixels[y * tex_pitch + x*4 + 1] = 225;
					pixels[y * tex_pitch + x*4 + 2] = 225;
					pixels[y * tex_pitch + x*4 + 3] = bmp->buffer[row * bmp->pitch + col];
				}
			}

			Glyph temp;

			temp.atlas_pos.x = pen_x;
			temp.atlas_pos.y = pen_y;
			temp.size.x = bmp->width;
			temp.size.y = bmp->rows;

			temp.bearing.x = face->glyph->bitmap_left;
			temp.bearing.y = face->glyph->bitmap_top;
			temp.advance = face->glyph->advance.x >> 6;

			glyphs_.push_back(temp);

			if (face->glyph->bitmap_top > tallest_glyph_height_) {
				tallest_glyph_height_ = face->glyph->bitmap_top;
			}

			pen_x += (bmp->pitch) + 1;
		}

		return Texture(pixels, tex_width, tex_height);
	}

	int Font::GetStringPixelWidth(const std::string& string)
	{
		int width = 0;

		for (const auto& c : string) {
			width += glyphs_[c].advance;
		}
		return width;
	}

}
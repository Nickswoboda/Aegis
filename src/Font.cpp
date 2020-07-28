#include "Font.h"
#include "Assert.h"
#include "Application.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <numeric>

namespace Aegis {
	std::shared_ptr<Font> Font::Create(const std::string& path, int size, int num_glyphs)
	{
		FT_Library library;
		FT_Face face;

		int error = FT_Init_FreeType(&library);
		if (!error){
			error = FT_New_Face(library, path.c_str(), 0, &face);
		}
		if (!error){
			error = FT_Set_Pixel_Sizes(face, size, size);
		}
		//if the font font can not be loaded for whatever reason, send default font instead of crashing program. Only crash if both fonts are not working
		if (error){
			if (Application::GetFont()){
				std::cout << "Unable to create font " << path << ". Initializing with default hardcoded font\n";
				return Application::GetFont();
			}
			
			AE_ASSERT(false, "Unable to create font " + path + " and unable to initialize hardcoded font\n"); 
		}

		return std::make_shared<Font>(library, face, path, size, num_glyphs); 

		
	}
	Font::Font(FT_Library& library, FT_Face& face, const std::string& path, int size, int num_glyphs)
		: font_name_(path), size_(size), num_glyphs_(num_glyphs)
	{
		atlas_ = CreateTextureAtlas(face);
		SetGlyphSubTextures();

		FT_Done_Face(face);
		FT_Done_FreeType(library);
	}

	Font::Font(const std::string& path, int size, int num_glyphs)
		: font_name_(path), size_(size), num_glyphs_(num_glyphs)
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
		SetGlyphSubTextures();

		FT_Done_Face(face);
		FT_Done_FreeType(library);
	}

	Font::Font(const std::string& name, const unsigned char* data, unsigned int data_size, int font_size, int num_glyphs)
		:num_glyphs_(num_glyphs)
	{
		font_name_ = name;
		size_ = font_size;
		
		FT_Library library;
		FT_Face face;

		int error = FT_Init_FreeType(&library);
		AE_ASSERT(error == 0, "Unable to initialize FreeType.");

		error = FT_New_Memory_Face(library, (FT_Byte*)data, data_size, 0, &face);
		AE_ASSERT(error == 0, "Unable to read font.");

		error = FT_Set_Pixel_Sizes(face, font_size, font_size);
		AE_ASSERT(error == 0, "Unable to set pixel size");

		atlas_ = CreateTextureAtlas(face);
		SetGlyphSubTextures();

		FT_Done_Face(face);
		FT_Done_FreeType(library);	
	}

	std::shared_ptr<Texture> Aegis::Font::CreateTextureAtlas(const FT_Face& face)
	{
		//src https ://gist.github.com/baines/b0f9e4be04ba4e6f56cab82eef5008ff
		//adapted to use 4channels per pixel

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

		return std::make_shared<Texture>(pixels, tex_width, tex_height);
	}

	void Font::SetGlyphSubTextures()
	{
		for (auto& glyph : glyphs_) {
			glyph.sub_texture_ = std::make_shared<SubTexture>(atlas_, glyph.atlas_pos, glyph.size);
		}
	}

	Vec2 Font::GetStringPixelSize(const std::string& string)
	{
		int width = 0;
		int height = 0;

		for (const auto& c : string) {
			auto glyph = glyphs_[c];
			width += glyph.advance;
			if (glyph.size.y + (tallest_glyph_height_ - glyph.bearing.y) > height) {
				//tallest glyph - bearing.y = the distance from top baseline
				height = glyph.size.y + (tallest_glyph_height_ - glyph.bearing.y);
			}
		}
		return Vec2(width, height);
	}
}

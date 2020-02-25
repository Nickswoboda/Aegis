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
			std::cout << "UNable to initialize freetype.";
		}
		error = FT_New_Face(library, path.c_str(), 0, &face);
		if (error == FT_Err_Unknown_File_Format)
		{
			std::cout << "Font format not supported";
		}
		else if (error)
		{
			std::cout << "Unable to read font";
		}

		error = FT_Set_Pixel_Sizes(face, size, size);

		error = FT_Load_Char(face, 'A', FT_LOAD_RENDER);

		texture_ = std::make_unique<Texture>(face->glyph->bitmap);
		
		auto test = face->glyph->bitmap.buffer[255];




	}
}
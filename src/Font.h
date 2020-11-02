#pragma once

#include "Renderer/Texture.h"
#include "Math/Vec2.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#include <unordered_map>
#include <memory>
#include <vector>
namespace Aegis {

	struct Glyph
	{
		std::shared_ptr<Texture> texture_;
		Vec2 atlas_pos;
		Vec2 size;
		Vec2 bearing;
		int advance;
	};

	class Font 
	{
	public:
		static std::shared_ptr<Font> Create(const std::string& path, int size, int num_glyphs = 128);
		Font(const std::string& path, int size, int num_glyphs = 128);
		Font(const std::string& name, const unsigned char* data, unsigned int data_size, int font_size, int num_glyphs = 128);  
		std::shared_ptr<Texture> CreateTextureAtlas(const FT_Face& face);
		void SetGlyphSubTextures();
		Vec2 GetStringPixelSize(const std::string& string);

		std::string font_name_;
		int size_;
		std::vector<Glyph> glyphs_;
		//used to align to top-left corner when rendering
		int tallest_glyph_height_ = 0;
		std::shared_ptr<Texture> atlas_;
		int num_glyphs_ = 0;
		Font(FT_Library& library, FT_Face& face, const std::string& path, int size, int num_glyphs = 128);

	};

}

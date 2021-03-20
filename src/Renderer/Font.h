#pragma once

#include "Texture.h"
#include "../Math/Vec2.h"

#include <ft2build.h>
#include FT_FREETYPE_H


#include <unordered_map>
#include <memory>
#include <vector>
namespace Aegis {

	struct Glyph
	{
		Vec4 texture_coords_;
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
		void SetGlyphTextureCoords();
		Vec2 GetStringPixelSize(const std::string& string) const;

		std::string font_name_;
		int size_;
		std::vector<Glyph> glyphs_;
		//used to allow specifying top-left corner when rendering
		//while keeping a consistent baseline
		int highest_glyph_bearing_ = 0;
		std::shared_ptr<Texture> atlas_;
		int num_glyphs_ = 0;
		Font(FT_Library& library, FT_Face& face, const std::string& path, int size, int num_glyphs = 128);

	};

}

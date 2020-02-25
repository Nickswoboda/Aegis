#pragma once

#include <string>


#include <ft2build.h>
#include FT_FREETYPE_H

namespace Aegis {
	class Texture
	{
	public:
		Texture();
		Texture(FT_Bitmap data);
		Texture(const std::string& path);

		void Bind();

		unsigned int ID_ = 0;
	};
}
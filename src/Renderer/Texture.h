#pragma once

#include <string>


#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
namespace Aegis {
	class Texture
	{
	public:
		Texture();
		Texture(FT_Bitmap data);
		Texture(const std::string& path);
		Texture(char* data, int width, int height);
		void Bind();

		unsigned int ID_ = 0;
		unsigned int width_;
		unsigned int height_;
	};
}
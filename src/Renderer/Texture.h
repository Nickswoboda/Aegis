#pragma once

#include <string>

namespace Aegis {
	class Texture
	{
	public:
		Texture();
		~Texture();
		explicit Texture(const std::string& path);
		Texture(unsigned char* data, int width, int height);
		void Bind();

		unsigned int ID_ = 0;
		unsigned int width_;
		unsigned int height_;
	};
}
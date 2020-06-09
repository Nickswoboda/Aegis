#pragma once

#include <string>

namespace Aegis {
	class Texture
	{
	public:
		explicit Texture(const std::string& path);
		Texture(unsigned char* data, int width, int height);

		~Texture();
		void Bind();

		unsigned int ID_ = 0;
		unsigned int width_;
		unsigned int height_;
	};
}
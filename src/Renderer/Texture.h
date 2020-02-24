#pragma once

#include <string>
namespace Aegis {
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& path);

		void Bind();

		unsigned int ID_ = 0;
	};
}
#pragma once

#include "../Math/Vec2.h"
#include "../Math/Vec4.h"

#include <memory>
#include <string>
#include <vector>

namespace Aegis {

	class Font;

	class Texture
	{
	public:
		static std::shared_ptr<Texture> Create(const std::string& path);
		static std::shared_ptr<Texture> Create(unsigned char* data, int width, int height, int channels);

		static std::shared_ptr<Texture> CreateFromText(const std::string& text, const Font& font);

		~Texture();
		void Bind();

		Vec2 size_;
		unsigned int ID_ = 0;

	private:
		Texture(unsigned char* data, int width, int height, int channels);
		static std::shared_ptr<Texture> GetPlaceholderTexture();
	};
}

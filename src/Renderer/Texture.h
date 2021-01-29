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

		static std::shared_ptr<Texture> TextureFromText(const std::string& text, std::shared_ptr<Font> font);
		static std::shared_ptr<Texture> SubTexture(const std::shared_ptr<Texture>& texture, Vec2 pos_on_tex, Vec2 size);

		~Texture();
		void Bind();

		Vec4 tex_coords_ = {0.0f, 0.0f, 1.0f, 1.0f};
		Vec2 size_;
		unsigned int ID_ = 0;

		//blank texture object used for subtextures
	private:
		Texture(unsigned char* data, int width, int height, int channels);
		Texture() = default;
		static std::shared_ptr<Texture> GetPlaceholderTexture();
	};
}

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

		static std::shared_ptr<Texture> CreateFromText(const std::string& text, std::shared_ptr<Font> font);

		~Texture();
		void Bind();

		Vec4 tex_coords_ = { 0.0f, 0.0f, 1.0f, 1.0f };
		Vec2 size_;
		unsigned int ID_ = 0;

	private:
		Texture(unsigned char* data, int width, int height, int channels);
		static std::shared_ptr<Texture> GetPlaceholderTexture();
	};

	class SubTexture
	{
	public:
		SubTexture(std::shared_ptr<Texture> texture, Vec2 pos_on_tex, Vec2 size);
		static std::shared_ptr<SubTexture> Create(std::shared_ptr<Texture> texture, Vec2 pos_on_tex, Vec2 size);

		Vec4 tex_coords_;
		Vec2 size_;
		std::shared_ptr<Texture> texture_;
	};
}

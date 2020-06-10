#pragma once

#include "../Math/Vec2.h"
#include "../Math/Vec4.h"

#include <memory>
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

	class SubTexture 
	{
	public:
		SubTexture(const std::shared_ptr<Texture>& texture, Vec2 pos, Vec2 size);
		const std::shared_ptr<Texture> GetTexture() const { return texture_; }
		const Vec4& GetTexCoords() const { return tex_coords_; }
		
	private:
		std::shared_ptr<Texture> texture_;
		Vec2 pos_;
		Vec2 size_;
		Vec4 tex_coords_;
	};
}
#pragma once

#include "Renderer/Texture.h"
#include "Math.h"

#include <memory>
namespace Aegis
{
	class Sprite
	{
	public:
		Sprite(const std::shared_ptr<Texture>& texture)
		{
			texture_ = texture;
			size_.x = texture->width_;
			size_.y = texture->width_;
			tex_coords_ = { 0.0f, 0.0f, 1.0f, 1.0f };
			color_ = { 1.0f, 1.0f, 1.0f, 1.0f };

		}
		std::shared_ptr<Texture> texture_;
		Vec2 pos_;
		Vec2 size_;
		Vec4 tex_coords_;
		Vec4 color_;
	};
}
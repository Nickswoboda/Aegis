#pragma once

#include "Renderer/Texture.h"
#include "Math/Vec2.h"
#include "Math/Vec4.h"

#include <memory>
namespace Aegis
{
	class Sprite
	{
	public:
		Sprite() {};
		explicit Sprite(Vec2 pos, Vec2 size, const std::shared_ptr<Texture>& texture, Vec2 subtex_pos = {0.0f, 0.0f}, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f})
			: texture_(std::make_shared<SubTexture>(texture, subtex_pos, size)), pos_(pos), size_(size),
				color_(color)
		{}

		std::shared_ptr<SubTexture> texture_;
		Vec2 pos_;
		Vec2 size_;
		Vec4 color_;
	};
}

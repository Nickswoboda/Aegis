#pragma once

#include "Renderer/Texture.h"
#include "Math/Vec2.h"
#include "Math/Vec4.h"
#include "Math/AABB.h"

#include <memory>
namespace Aegis
{
	class Sprite
	{
	public:
		Sprite() = default;
		explicit Sprite(Vec2 pos, Vec2 size, const std::shared_ptr<Texture>& texture, Vec2 subtex_pos = {0.0f, 0.0f}, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f})
			: texture_(SubTexture::Create(texture, subtex_pos, size)), rect_(pos.x, pos.y, size.x, size.y),
				color_(color)
		{}

		std::shared_ptr<SubTexture> texture_;
		AABB rect_;
		Vec4 color_;

	};
}

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
		explicit Sprite(std::shared_ptr<Texture>);
		Sprite(std::shared_ptr<Texture> texture, AABB subtex_rect);

		void SetSubTextureRect(AABB subtex_rect);
		AABB GetSubTextureRect() const;
		
		Vec4 GetTextureCoords() const;

		std::shared_ptr<Texture> texture_;
		Vec4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};
		Vec2 scale_ = {1.0f, 1.0f};

	private:

		void UpdateTextureCoords();
		Vec4 texture_coords_;
		AABB subtexture_rect_;

	};
}

#pragma once

#include "Texture.h"
#include "Transform.h"
#include "../Math/Vec2.h"
#include "../Math/Vec4.h"
#include "../Math/AABB.h"

#include <memory>
namespace Aegis
{
	class Sprite
	{
	public:
		Sprite() = default;
		explicit Sprite(std::shared_ptr<Texture>);
		Sprite(std::shared_ptr<Texture> texture, AABB subtex_rect);

		void Draw() const;

		void SetSubTextureRect(AABB subtex_rect);
		AABB GetSubTextureRect() const;
		
		Vec4 GetTextureCoords() const;
		void SetHorizontalFlip(bool flip);
		bool GetHorizontalFlip() const;
		AABB GetRect() const;
		Transform& GetTransform();

		std::shared_ptr<Texture> texture_;
		Vec4 color_ = {1.0f, 1.0f, 1.0f, 1.0f};

	private:
		void UpdateTextureCoords();
		Transform transform_;
		Vec4 texture_coords_;
		AABB subtexture_rect_;
		bool horizontally_flipped_ = false;

	};
}

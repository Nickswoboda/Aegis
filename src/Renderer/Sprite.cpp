#include "Sprite.h"

#include "Renderer.h"
#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Aegis{

	Sprite::Sprite(std::shared_ptr<Texture> texture)
		: texture_(texture)
	{
		SetSubTextureRect({ { 0,0 }, texture->size_ });
		texture_coords_ = {0.0f, 0.0f, 1.0f, 1.0f};
	}

	Sprite::Sprite(std::shared_ptr<Texture> texture, AABB subtex_rect)
		: texture_(texture), subtexture_rect_(subtex_rect)
	{
		UpdateTextureCoords();
		SetSubTextureRect(subtex_rect);
	}

	void Sprite::Draw() const
	{
		Transform to_global = transform_;
		to_global.SetScale(transform_.GetScale() * subtexture_rect_.size);
		DrawQuad(to_global, texture_->ID_, texture_coords_, color_);
	}

	void Sprite::SetSubTextureRect(AABB subtex_rect)
	{
		subtexture_rect_ = subtex_rect;
		transform_.SetOrigin((subtex_rect.size * transform_.GetScale()) / 2);
		UpdateTextureCoords();
	}

	AABB Sprite::GetSubTextureRect() const
	{
		return subtexture_rect_;
	}

	Vec4 Sprite::GetTextureCoords() const
	{
		return texture_coords_;
	}

	void Sprite::UpdateTextureCoords()
	{
		float x1 = subtexture_rect_.pos.x / texture_->size_.x;
		float y1 = subtexture_rect_.pos.y / texture_->size_.y;
		float x2 = (subtexture_rect_.pos.x + subtexture_rect_.size.x) / texture_->size_.x;
		float y2 = (subtexture_rect_.pos.y + subtexture_rect_.size.y) / texture_->size_.y;
		texture_coords_ = { x1, y1, x2, y2 };
	}

	void Sprite::SetHorizontalFlip(bool flip)
	{
		if (horizontally_flipped_ != flip) {
			float temp = texture_coords_.x;
			texture_coords_.x = texture_coords_.z;
			texture_coords_.z = temp;
			horizontally_flipped_ = flip;
		}
	}

	bool Sprite::GetHorizontalFlip() const
	{
		return horizontally_flipped_;
	}

	AABB Sprite::GetRect() const 
	{
		Vec2 size = subtexture_rect_.size * transform_.GetScale();

		return {transform_.GetPosition(), size};

	}

	Transform& Sprite::GetTransform()
	{
		return transform_;
	}

}

#include "Sprite.h"

#include "Renderer/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Aegis{

	Sprite::Sprite(std::shared_ptr<Texture> texture)
		: texture_(texture)
	{
		subtexture_rect_ = {0,0, texture->size_.x, texture->size_.y};
		texture_coords_ = {0.0f, 0.0f, 1.0f, 1.0f};
	}

	Sprite::Sprite(std::shared_ptr<Texture> texture, AABB subtex_rect)
		: texture_(texture), subtexture_rect_(subtex_rect)
	{
		UpdateTextureCoords();
	}

	void Sprite::Draw() const
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position_.x, position_.y, 0.0f));

		//move origin to center of sprite, rotate, then move back
		Vec2 size = subtexture_rect_.size * scale_;
		transform = glm::translate(transform, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::translate(transform, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));

		DrawQuad(transform, texture_->ID_, texture_coords_, color_);
	}

	void Sprite::SetSubTextureRect(AABB subtex_rect)
	{
		subtexture_rect_ = subtex_rect;
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
		Vec2 size = subtexture_rect_.size * scale_;

		return {position_.x, position_.y, size.x, size.y};

	}

}

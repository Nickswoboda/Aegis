#include "SpriteWidget.h"

#include "../Renderer/Renderer.h"

namespace Aegis {
	SpriteWidget::SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture)
		: sprite_(texture) 
	{
		sprite_.GetTransform().SetPosition(pos);
		rect_ = sprite_.GetRect();
	}

	SpriteWidget::SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture, AABB subtex_rect)
		: sprite_(texture, subtex_rect)
	{
		sprite_.GetTransform().SetPosition(pos);
		rect_ = sprite_.GetRect();
	}

	void SpriteWidget::Render() const
	{
		if (visible_) {
			sprite_.Draw();
		}
	}

	void SpriteWidget::SetSubTextureRect(const AABB& subtex_rect)
	{
		sprite_.SetSubTextureRect(subtex_rect);
	}

	void SpriteWidget::SetScale(Vec2 scale)
	{
		sprite_.GetTransform().SetScale(scale);
		rect_ = sprite_.GetRect();
	}

	void SpriteWidget::SetPos(Vec2 pos)
	{
		rect_.pos = pos;
		sprite_.GetTransform().SetPosition(pos);
	}
}

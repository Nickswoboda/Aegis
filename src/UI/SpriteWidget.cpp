#include "SpriteWidget.h"

#include "../Renderer/Renderer.h"

namespace Aegis {
	SpriteWidget::SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture)
		: sprite_(texture), pos_(pos) 
	{
		rect_ = { pos.x, pos.y, texture->size_.x, texture->size_.y };
	}

	SpriteWidget::SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture, AABB subtex_rect)
		: sprite_(texture, subtex_rect), pos_(pos) 
	{
		rect_ = { pos.x, pos.y, subtex_rect.size.x, subtex_rect.size.y };
	}

	void SpriteWidget::Render() const
	{
		if (visible_) {
			DrawSubTexture(rect_.pos, sprite_.GetRect().size, *sprite_.texture_, sprite_.GetTextureCoords());
		}
	}
}

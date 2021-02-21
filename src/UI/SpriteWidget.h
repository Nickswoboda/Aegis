#pragma once

#include "Widget.h"
#include "../Sprite.h"

namespace Aegis{

	class SpriteWidget : public Widget
	{
	public:

		SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture);
		SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture, AABB subtex_rect);

		void OnEvent(Event& event) override {}
		void Render() const override;

		Sprite sprite_;
		Vec2 pos_;

	};
}

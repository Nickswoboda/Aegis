#pragma once

#include "Widget.h"
#include "../Renderer/Sprite.h"

namespace Aegis{

	class SpriteWidget : public Widget
	{
	public:

		SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture);
		SpriteWidget(const Vec2 pos, std::shared_ptr<Texture> texture, AABB subtex_rect);

		void OnEvent(Event& event) override {}
		void Render() const override;

		void SetPos(Vec2 pos) override;

		void SetSubTextureRect(const AABB& subtex_rect);
		void SetScale(Vec2 scale);


	private:
		Sprite sprite_;
	};
}

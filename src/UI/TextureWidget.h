#pragma once

#include "Widget.h"

namespace Aegis{
	class TextureWidget : public Widget
	{
	public:

		TextureWidget(std::shared_ptr<Texture> texture, const Vec2 pos, const Vec2 size, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		TextureWidget(const Vec4& color, const Vec2 pos, const Vec2 size);

		void OnEvent(Event& event) override {};
		void Render() override;

		std::shared_ptr<Texture> texture_;
		Vec4 color_;
		Vec2 pos_;
		Vec2 size_;
	};
}

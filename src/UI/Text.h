#pragma once
#include "Widget.h"

namespace Aegis{
	class Text : public Widget
	{
	public:
		Text(const std::string& text, Vec2 pos, Vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});

		void OnEvent(Event& event) override {};
		void Render(float delta_time) override;

		std::string text_;
		Vec2 pos_;
		Vec4 color_;
	};
}

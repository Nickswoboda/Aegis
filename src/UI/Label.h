#pragma once
#include "Widget.h"

namespace Aegis{
	class Label : public Widget
	{
	public:
		Label(const std::string& text, Vec2 pos, Vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});

		void OnEvent(Event& event) override {};
		void Render(float delta_time = 0) override;

		std::string text_;
		Vec2 pos_;
		Vec4 color_;
	};
}

#pragma once
#include "Widget.h"

namespace Aegis{
	class Label : public Widget
	{
	public:
		Label(const std::string& text, Vec2 pos, Vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});

		void OnEvent(Event& event) override {};
		void Render() override;

		void SetText(const std::string& text);

		Vec4 color_;

	private:
		std::string text_;
	};
}

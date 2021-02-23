#pragma once

#include "../Math/Vec2.h"
#include "Button.h"
#include "UILayer.h"
#include "Label.h"

namespace Aegis{

	class Dialog : public Widget
	{
	public:
		Dialog(const std::string& text, const AABB& rect);
		
		void OnEvent(Event& event) override;
		void Render() const override;

		std::unique_ptr<Button> accept_button_;
		std::unique_ptr<Button> reject_button_;
		std::unique_ptr<Label> text_;
	};
}

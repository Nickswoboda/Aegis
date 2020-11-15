#pragma once

#include "../Math/Vec2.h"
#include "Button.h"
#include "UILayer.h"
#include "Label.h"

namespace Aegis{

	class Dialog : public Widget
	{
	public:
		Dialog(const std::string& text, Vec2 pos_, Vec2 size_);
		
		void OnEvent(Event& event) override;
		void Render(float delta_time = 0.0f) override;

		void SetAcceptedCallback(std::function<void()> callback);
		void SetRejectedCallback(std::function<void()> callback);
		
		std::unique_ptr<Button> accept_button_;
		std::unique_ptr<Button> reject_button_;
		std::unique_ptr<Label> text_;
		
		Vec2 pos_;
		Vec2 size_;

	};
}

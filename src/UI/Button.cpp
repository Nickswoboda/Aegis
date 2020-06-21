#include "Button.h"

#include "../MouseCodes.h"
#include "../Application.h"
#include "../Renderer/Renderer.h"

namespace Aegis {
	Button::Button(AABB rect, const std::string& text, std::function<void()> callback)
		: rect_(rect), text_(text), callback_(callback)
	{
	}
	
	bool Button::IsPressed(int action)
	{
		//Only return true if mouse was both pressed and released within button rect
		if (PointInAABB(Application::GetWindow().GetMousePos(), rect_)) {
			if (action == AE_BUTTON_PRESS) {
				pressed_ = true;
			}
			else if (action == AE_BUTTON_RELEASE && pressed_) {
				pressed_ = false;
				return true;
			}
		}

		return false;
	}

	void Button::Render(float delta_time)
	{
		DrawQuad(rect_.pos, rect_.size, color_);

		if (!text_.empty()){
		Renderer2D::SetFont(font_);
		DrawText(text_, rect_.pos, { 1.0, 1.0f, 1.0f, 1.0f });
		}
	}

	void Button::OnEvent(Event& event)
	{
		auto click = dynamic_cast<MouseClickEvent*>(&event);
		if (click) {
			if (IsPressed(click->action_)) {
				callback_();
			}
		}
	}
}

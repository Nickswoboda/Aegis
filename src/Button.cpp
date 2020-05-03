#include "Button.h"

#include "MouseCodes.h"
#include "Application.h"
#include "Renderer/Renderer.h"

namespace Aegis {
	Button::Button(AABB rect)
		: rect_(rect)
	{
	}

	Button::Button(AABB rect, std::string text, std::shared_ptr<Font> font)
		: rect_(rect), text_(text), font_(font)
	{
	}

	bool Button::IsPressed(int action)
	{
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

	void Button::Render()
	{
		DrawQuad(rect_.pos, rect_.size, color_);

		if (!text_.empty()){
		Renderer2D::SetFont(font_);
		DrawText(text_, rect_.pos, { 1.0, 1.0f, 1.0f, 1.0f });
		}
	}
}
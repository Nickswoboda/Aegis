#include "Button.h"

#include "MouseCodes.h"
#include "Application.h"
#include "Renderer/Renderer.h"

namespace Aegis {
	Button::Button(Aegis::AABB rect)
		: rect_(rect)
	{
	}

	Button::Button(Aegis::AABB rect, std::string text, std::shared_ptr<Aegis::Font> font)
		: rect_(rect), text_(text), font_(font)
	{
	}

	bool Button::IsPressed(int action)
	{
		if (PointInAABB(Application::GetMousePos(), rect_)) {
			if (action == AE_BUTTON_PRESS) {
				pressed_ = true;
			}
			else if (action == AE_BUTTON_RELEASE) {
				return true;
			}
		}

		return false;
	}

	void Button::Render()
	{
		Aegis::DrawQuad(rect_.pos, rect_.size, color_);

		if (!text_.empty()){
		Aegis::Renderer2D::SetFont(font_);
		Aegis::DrawText(text_, rect_.pos, { 1.0, 1.0f, 1.0f, 1.0f });
		}
	}
}
#include "Label.h"

#include "../Renderer/Renderer.h"

namespace Aegis{

	Label::Label(const std::string& text, Vec2 pos, Vec4 color)
		: text_(text), pos_(pos), color_(color)
	{
	};

	void Label::Render(float delta_time)
	{
		Renderer2D::SetFont(font_);
		DrawText(text_, pos_, color_);
	};
}

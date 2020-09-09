#include "Text.h"

#include "../Renderer/Renderer.h"

namespace Aegis{

	Text::Text(const std::string& text, Vec2 pos, Vec4 color)
		: text_(text), pos_(pos), color_(color)
	{
	};

	void Text::Render(float delta_time)
	{
		DrawText(text_, pos_, color_);
	};
}

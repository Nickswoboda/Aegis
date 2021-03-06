#include "Label.h"

#include "../Renderer/Renderer.h"

namespace Aegis{

	Label::Label(const std::string& text, Vec2 pos, Vec4 color)
		:color_(color), text_(text)
	{
		auto size = font_->GetStringPixelSize(text);
		rect_ = {pos.x, pos.y, size.x, size.y};
	};

	void Label::Render() const
	{
		if(visible_){
			Renderer2D::SetFont(font_);
			DrawText(text_, rect_.pos, color_);
		}
	}

	void Label::SetFont(std::shared_ptr<Aegis::Font> font)
	{
		font_ = font;
		SetSize(font_->GetStringPixelSize(text_));
	}

	void Label::SetText(const std::string& text)
	{
		text_ = text;
		SetSize(font_->GetStringPixelSize(text));
	}

	const std::string& Label::GetText() const
	{
		return text_;
	}

}

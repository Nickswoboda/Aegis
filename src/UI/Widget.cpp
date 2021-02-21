#include "Widget.h"
#include "../Application.h"

namespace Aegis {

	Widget::Widget(AABB rect)
		:Object(), rect_(rect), font_(Application::GetFont())
	{}
	void Widget::SetPos(Aegis::Vec2 pos)
	{
		rect_.pos = pos;
	}
	void Widget::SetSize(Aegis::Vec2 size)
	{
		rect_.size = size;
	}
	const AABB& Widget::GetRect() const
	{
		return rect_;
	}
	void Widget::SetFont(std::shared_ptr<Font> font)
	{
		font_ = font;
	}
}

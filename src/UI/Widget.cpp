#include "Widget.h"
#include "../Core/Application.h"

namespace Aegis {

	Widget::Widget()
		:Object(), font_(Application::GetFont())
	{
		AddSignal("size changed");
	}
	void Widget::SetPos(Aegis::Vec2 pos)
	{
		rect_.pos = pos;
	}
	void Widget::SetSize(Aegis::Vec2 size)
	{
		rect_.size = size;
		Emit("size changed");
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

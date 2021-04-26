#include "Container.h"
#include "../Renderer/Renderer.h"
#include "../Core/Assert.h"

namespace Aegis{
	Container::Container(AABB rect, Orientation orientation, int padding, Alignment alignment)
		:Widget(rect), padding_(padding), orientation_(orientation), occupied_space_(padding)
	{
		SetAlignment(alignment);
	}

	void Container::OnEvent(Event& event)
	{
		for (auto& widget : widgets_) {
			if (widget->visible_) {
				widget->OnEvent(event);
				if (event.handled_) {
					return;
				}
			}
		}
	}

	void Container::Render() const
	{
		DrawQuad(rect_.pos, rect_.size, bg_color_);
		for (auto& widget : widgets_) {
			widget->Render();
		}
	}

	void Container::SetPos(Aegis::Vec2 pos)
	{
		Vec2 offset = pos - rect_.pos;
		rect_.pos = pos;

		for (auto& widget : widgets_){
			widget->SetPos(widget->GetRect().pos + offset);
		}
	}

	void Container::AddWidget(std::shared_ptr<Widget> widget)
	{
		//TODO: resize widgets if they dont fit normally
		AE_ASSERT(WidgetFits(*widget), "Unable to add widget to container. Not enough space");

		widgets_.push_back(widget);
		widget->ConnectSignal("size changed", [&](){UpdateWidgets();});
		UpdateWidgets();
	}

	bool Container::WidgetFits(const Widget& widget) const
	{ 
		if (orientation_ == Vertical){
			return (widget.GetRect().size.x <= rect_.size.x &&
					occupied_space_ + widget.GetRect().size.y + padding_ <= rect_.size.y);
		}

		return (widget.GetRect().size.y <= rect_.size.y &&
				occupied_space_ + widget.GetRect().size.x + padding_ <= rect_.size.x);
	}

	void Container::UpdateWidgets()
	{
		occupied_space_ = 0;
		if (orientation_ == Vertical){
			for (const auto& widget : widgets_){
				occupied_space_ += widget->GetRect().size.y + padding_;
			}
		} else {
			for (const auto& widget : widgets_){
				occupied_space_ += widget->GetRect().size.x + padding_;
			}
		}

		Vec2 pen_pos;
		if (orientation_ == Orientation::Vertical){
			//assume align top
			pen_pos.y = rect_.pos.y + padding_;
			if (alignment_ & Alignment::Bottom){
				pen_pos.y += rect_.size.y - occupied_space_;
			} else if (alignment_ & Alignment::VCenter){
				pen_pos.y += (rect_.size.y - occupied_space_) / 2;
			}
		}
		else {
			//assume align left
			pen_pos.x = rect_.pos.x + padding_;
			if (alignment_ & Alignment::Right) {
				pen_pos.x += rect_.size.x - occupied_space_;
			} else if (alignment_ & Alignment::HCenter) {
				pen_pos.x += (rect_.size.x - occupied_space_) / 2;
			}
		}

		for (auto& widget : widgets_) {
			AlignWidget(*widget, pen_pos);
		}
	}

	void Container::SetAlignment(Alignment alignment)
	{
		//make sure there is at least one valid flag set for both v and h alignment
		if (!(alignment & Alignment::Top) && !(alignment & Alignment::Bottom) && !(alignment & Alignment::VCenter)) {
			alignment = alignment | Alignment::Top;
		}
		if (!(alignment & Alignment::Left) && !(alignment & Alignment::Right) && !(alignment & Alignment::HCenter)) {
			alignment = alignment | Alignment::Left;
		}
		alignment_ = alignment;
	}

	void Container::AlignWidget(Widget& widget, Vec2& pen_pos)
	{
		if (orientation_ == Orientation::Vertical){
			if (alignment_ & Alignment::HCenter){
				int width_diff = rect_.size.x - widget.GetRect().size.x;
				pen_pos.x = rect_.pos.x + (width_diff / 2);
			} else if (alignment_ & Alignment::Left){
				pen_pos.x = rect_.pos.x;
			} else if (alignment_ & Alignment::Right){
				int right_edge = rect_.pos.x + rect_.size.x;
				pen_pos.x = right_edge - widget.GetRect().size.x;
			}
			widget.SetPos(pen_pos);
			pen_pos.y += widget.GetRect().size.y + padding_;
		}
		else {
			if (alignment_ & Alignment::VCenter) {
				int height_diff = rect_.size.y - widget.GetRect().size.y;
				pen_pos.y = rect_.pos.y + (height_diff / 2);
			} else if (alignment_ & Alignment::Top){
				pen_pos.y = rect_.pos.y;
			} else if (alignment_ & Alignment::Bottom) {
				int bottom_edge = rect_.pos.y + rect_.size.y;
				pen_pos.y = bottom_edge - widget.GetRect().size.y;
			}
			widget.SetPos(pen_pos);
			pen_pos.x += widget.GetRect().size.x + padding_;
		}
	}
}

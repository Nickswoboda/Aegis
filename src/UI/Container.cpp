#include "Container.h"

namespace Aegis{
	Container::Container(AABB rect, int padding)
		:rect_(rect), padding_(padding)
	{
	}
	VContainer::VContainer(AABB rect, int padding, Alignment alignment)
		:Container(rect, padding), alignment_(alignment)
	{
		
	}
	void VContainer::AddWidget(UIWidget* widget)
	{
		widgets_.push_back(widget);
		UpdateWidgets();
	}
	void VContainer::UpdateWidgets()
	{
		int pen_y = rect_.pos.y + padding_;

		for (auto& widget : widgets_){
			widget->rect_.pos.y = pen_y;

			AlignWidget(widget, alignment_);
			pen_y += widget->rect_.size.y + padding_;
		}
	}
	void VContainer::AlignWidget(UIWidget* widget, Alignment alignment)
	{
		switch (alignment){
			case Alignment::Center:
			{
				int width_diff = rect_.size.x - widget->rect_.size.x;
				widget->rect_.pos.x = rect_.pos.x + (width_diff / 2);
				break;
			}
			case Alignment::Left: 
			{
				widget->rect_.pos.x = rect_.pos.x;
				break;
			}
			case Alignment::Right:
			{
				int right_edge = rect_.pos.x + rect_.size.x;
				widget->rect_.pos.x = right_edge - widget->rect_.size.x;
				break;
			}
		}
	}
}

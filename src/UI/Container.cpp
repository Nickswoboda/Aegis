#include "Container.h"
#include "../Renderer/Renderer.h"

namespace Aegis{
	Container::Container(AABB rect, int padding, Alignment alignment)
		:rect_(rect), padding_(padding), alignment_(alignment), bg_color_({0.0f, 0.0f, 1.0f, 0.4f})
	{
	}

	void Container::Render()
	{
		DrawQuad(rect_.pos, rect_.size, bg_color_);
	}

	VContainer::VContainer(AABB rect, int padding, Alignment alignment)
		:Container(rect, padding, alignment)
	{
		
	}

	void Container::AddWidget(UIWidget* widget)
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

	HContainer::HContainer(AABB rect, int padding, Alignment alignment)
		:Container(rect, padding, alignment)
	{

	}

	void HContainer::UpdateWidgets()
	{
		int pen_x = rect_.pos.x + padding_;

		for (auto& widget : widgets_){
			widget->rect_.pos.x = pen_x;

			AlignWidget(widget, alignment_);
			pen_x += widget->rect_.size.x + padding_;
		}
	}

	void HContainer::AlignWidget(UIWidget* widget, Alignment alignment)
	{
		switch (alignment){
			case Alignment::Center:
			{
				int height_diff = rect_.size.y - widget->rect_.size.y;
				widget->rect_.pos.y = rect_.pos.y + (height_diff / 2);
				break;
			}
			case Alignment::Top: 
			{
				widget->rect_.pos.y = rect_.pos.y;
				break;
			}
			case Alignment::Bottom:
			{
				int bottom_edge = rect_.pos.y + rect_.size.y;
				widget->rect_.pos.y = bottom_edge - widget->rect_.size.y;
				break;
			}
		}
	}
}

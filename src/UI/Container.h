#pragma once

#include "Widget.h"
#include "../Math/Vec4.h"

namespace Aegis{
	class Container
	{
	public:
		enum Orientation
		{
			Horizontal,
			Vertical
		};

		enum Alignment
		{
			Top,
			Bottom,
			Left,
			Right,
			Center
		};
		Container(AABB rect_, Orientation orientation, int padding, Alignment alignment);
		~Container(){} 
		void AddWidget(Widget* widget);
		void UpdateWidgets();
		void AlignWidget(Widget* widget, Alignment alignment);
		void Render();


		std::vector<Widget*> widgets_;
		Vec4 bg_color_;
		AABB rect_;
		int padding_;
		Alignment alignment_;
		Orientation orientation_;
	};
}


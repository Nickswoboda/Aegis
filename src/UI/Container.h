#pragma once

#include "Widget.h"
#include "../Math/Vec4.h"

namespace Aegis{
	class Container
	{
	public:
		enum Alignment
		{
			Top,
			Bottom,
			Left,
			Right,
			Center
		};
		Container(AABB rect_, int padding, Alignment alignment);
		virtual ~Container(){} 
		void AddWidget(Widget* widget);
		virtual void UpdateWidgets() = 0;
		virtual void AlignWidget(Widget* widget, Alignment alignment) = 0;
		void Render();


		std::vector<Widget*> widgets_;
		AABB rect_;
		int padding_;
		Alignment alignment_;
		Vec4 bg_color_;
	};

	class VContainer : public Container
	{
	public:
		VContainer(AABB rect, int padding, Alignment alignment);
		~VContainer() {}

		virtual void UpdateWidgets() override;
		virtual void AlignWidget(Widget* widget, Alignment alignment) override;

	};

	class HContainer : public Container
	{
	public:

		HContainer(AABB rect, int padding, Alignment alignment);
		~HContainer() {}

		virtual void UpdateWidgets() override;
		virtual void AlignWidget(Widget* widget, Alignment alignment) override;

	};
}


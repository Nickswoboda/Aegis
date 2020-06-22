#pragma once

#include "UIWidget.h"

namespace Aegis{
	class Container
	{
	public:
		Container(AABB rect_, int padding);
		virtual ~Container(){} 
		virtual void AddWidget(UIWidget* widget) = 0;
		virtual void UpdateWidgets() = 0;


		std::vector<UIWidget*> widgets_;
		AABB rect_;
		int padding_;

	};

	class VContainer : public Container
	{
	public:
		enum class Alignment
		{
			Right,
			Left,
			Center,
		};
		VContainer(AABB rect, int padding, Alignment alignment);
		~VContainer() {}

		virtual void AddWidget(UIWidget* widget) override;
		virtual void UpdateWidgets() override;
		void AlignWidget(UIWidget* widget, Alignment alignment);

		Alignment alignment_;
	};
}

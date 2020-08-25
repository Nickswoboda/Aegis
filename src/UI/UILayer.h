#pragma once

#include "../Layer.h"
#include "Widget.h"
#include "Button.h"
#include "Dropdown.h"
#include "Checkbox.h"
#include "Container.h"

#include <vector>

namespace Aegis{
	class UILayer : public Layer
	{
	public:

		UILayer();

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void Render(float delta_time) override;
		
		void SetFont(std::shared_ptr<Font>& font_);

		template<typename T>
		std::shared_ptr<T> AddWidget(T* widget)
		{
			auto ref = std::shared_ptr<T>(widget);
			widget->SetFont(font_);
			widgets_.push_back(ref);
			return ref;
		}
		std::shared_ptr<Container> AddContainer(AABB rect, Container::Orientation orientation, int padding, Container::Alignment alignment);

		std::vector<std::shared_ptr<Container>> containers_;
		std::vector<std::shared_ptr<Widget>> widgets_;
		std::shared_ptr<Font> font_;
	};
}




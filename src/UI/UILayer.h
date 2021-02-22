#pragma once

#include "../Core/Layer.h"
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
		
		void SetFont(std::shared_ptr<Font> font_);

		template<typename T, typename... Args>
		std::shared_ptr<T> AddWidget(Args&&... args)
		{
			auto ref = std::shared_ptr<T>(new T(std::forward<Args>(args)...));
			ref->SetFont(font_);
			widgets_.push_back(ref);
			return ref;
		}

		std::vector<std::shared_ptr<Container>> containers_;
		std::vector<std::shared_ptr<Widget>> widgets_;
		std::shared_ptr<Font> font_;
	};
}




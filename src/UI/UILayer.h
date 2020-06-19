#pragma once

#include "../Layer.h"
#include "UIWidget.h"
#include "Button.h"
#include "Dropdown.h"
#include <vector>

namespace Aegis{
	class UILayer : public Layer
	{
	public:

		~UILayer();

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void Render(float delta_time) override;

		Button* AddButton(AABB rect, const std::string& text, std::shared_ptr<Font> font, std::function<void()> callback);
		Dropdown* AddDropdown(const std::string& label, AABB rect);
		std::vector<UIWidget*> widgets_;

	};
}



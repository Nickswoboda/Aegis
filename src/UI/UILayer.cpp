#include "UILayer.h"

namespace Aegis {

	void UILayer::OnUpdate()
	{
	}
	void UILayer::OnEvent(Event& event)
	{
		for (auto& widget : widgets_) {
			widget->OnEvent(event);
		}
	}
	void UILayer::Render(float delta_time)
	{
	}
	Button* UILayer::AddButton(AABB rect, const std::string& text, std::shared_ptr<Font> font, std::function<void()> callback)
	{
		Button* button = new Button(rect, text, font, callback);
		widgets_.push_back(button);

		return button;
	}
}
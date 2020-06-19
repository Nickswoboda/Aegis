#include "UILayer.h"

namespace Aegis {

	UILayer::~UILayer()
	{
		for (auto& widget : widgets_){
			delete widget;
		}
	}
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
		for (auto& widget : widgets_) {
			widget->Render(delta_time);
		}

	}
	Button* UILayer::AddButton(AABB rect, const std::string& text, std::shared_ptr<Font> font, std::function<void()> callback)
	{
		Button* button = new Button(rect, text, font, callback);
		widgets_.push_back(button);

		return button;
	}

	Dropdown* UILayer::AddDropdown(const std::string& label, AABB rect)
	{
		Dropdown* dropdown = new Dropdown(label, rect);
		widgets_.push_back(dropdown);

		return dropdown;
	}
}

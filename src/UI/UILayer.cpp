#include "UILayer.h"
#include "../Application.h"

namespace Aegis {

	UILayer::UILayer()
	{
		font_ = Application::GetFont();
	}
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
			if (event.handled_){
				return;
			}
		}
	}
	void UILayer::Render(float delta_time)
	{
		for (auto& widget : widgets_) {
			widget->Render(delta_time);
		}

	}
	Button* UILayer::AddButton(AABB rect, const std::string& text, std::function<void()> callback)
	{
		Button* button = new Button(rect, text, callback);
		button->SetFont(font_);
		widgets_.push_back(button);

		return button;
	}

	Dropdown* UILayer::AddDropdown(const std::string& label, AABB rect)
	{
		Dropdown* dropdown = new Dropdown(label, rect);
		dropdown->SetFont(font_);
		dropdown->button_pos_offset_ = font_->GetStringPixelWidth(label) + 15;
		widgets_.push_back(dropdown);

		return dropdown;
	}

	void UILayer::SetFont(std::shared_ptr<Font>& font)
	{
		font_ = font;
	}
}
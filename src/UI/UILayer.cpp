#include "UILayer.h"
#include "../Core/Application.h"

namespace Aegis {

	UILayer::UILayer()
	{
		font_ = Application::GetFont();
	}

	void UILayer::OnUpdate()
	{
	}

	void UILayer::OnEvent(Event& event)
	{
		for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it){
			(*it)->OnEvent(event);
			if (event.handled_){
				return;
			}
		}
	}

	void UILayer::AddWidget(std::shared_ptr<Widget> widget)
	{
		widgets_.push_back(widget);
	}

	void UILayer::Render(float dt)
	{
		Renderer2D::SetProjection(OrthographicProjection(0.0f, Application::GetWindow().GetResolution().x, Application::GetWindow().GetResolution().y, 0.0f));
		for (const auto& widget : widgets_) {
			if (widget->visible_){
				widget->Render();
			}
		}
	}

	void UILayer::SetFont(std::shared_ptr<Font> font)
	{
		font_ = font;
	}

}

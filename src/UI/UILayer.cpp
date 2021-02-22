#include "UILayer.h"
#include "../Application.h"

#include "glm/gtc/matrix_transform.hpp"
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
		for (auto& widget : widgets_) {
			widget->OnEvent(event);
			if (event.handled_){
				return;
			}
		}
	}

	void UILayer::Render(float dt)
	{
		Renderer2D::SetProjection(glm::ortho(0.0f, Application::GetWindow().GetResolution().x, Application::GetWindow().GetResolution().y, 0.0f));
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

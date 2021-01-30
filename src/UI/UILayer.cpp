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
			if (widget->visible_){
				widget->OnEvent(event);
				if (event.handled_){
					return;
				}
			}
		}
	}
	void UILayer::Render(float dt)
	{
		Renderer2D::SetProjection(glm::ortho(0.0f, Application::GetWindow().GetResolution().x, Application::GetWindow().GetResolution().y, 0.0f));
		for (const auto& container : containers_){
			container->Render();
		}
		for (const auto& widget : widgets_) {
			if (widget->visible_){
				widget->Render();
			}
		}

	}

	std::shared_ptr<Container> UILayer::AddContainer(AABB rect, Container::Orientation orientation, int padding, Container::Alignment alignment)
	{
		auto container = std::make_shared<Container>(rect, orientation, padding, alignment);
		containers_.push_back(container);
		return container;
	}

	void UILayer::SetFont(std::shared_ptr<Font>& font)
	{
		font_ = font;
	}

}

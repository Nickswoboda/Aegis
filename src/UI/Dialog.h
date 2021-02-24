#pragma once

#include "../Math/Vec2.h"
#include "Button.h"
#include "UILayer.h"
#include "Label.h"

namespace Aegis{

	class Dialog : public Widget
	{
	public:
		Dialog(const std::string& text, const AABB& rect);
		
		void OnEvent(Event& event) override;
		void Render() const override;

		void AddButton(const std::string& label, std::function<void()> callback);

		std::unique_ptr<Container> button_container_;
		std::unique_ptr<Label> text_;
	};
}

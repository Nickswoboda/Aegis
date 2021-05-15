#pragma once

#include "../Math/Vec2.h"
#include "Button.h"
#include "UILayer.h"
#include "Label.h"

namespace Aegis{

	class Dialog : public Widget
	{
	public:
		Dialog(const std::string& text);
		
		void OnEvent(Event& event) override;
		void Render() const override;
		
		void SetPos(Vec2 pos) override;

		virtual void AddButton(const std::string& label, std::function<void()> callback);

		HContainer button_container_;
		std::unique_ptr<Label> text_;
		Vec4 bg_color_ = {0.2f, 0.2f, 1.0f, 1.0f};
	};
}

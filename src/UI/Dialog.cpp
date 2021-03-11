#include "Dialog.h"

#include "../Renderer/Renderer.h"
#include "../Core/Application.h"

namespace Aegis{
	Dialog::Dialog(const std::string& text, const AABB& rect)
		:Widget(rect)
	{
		Vec2 text_size = font_->GetStringPixelSize(text);
		Vec2 text_pos = rect_.pos + Vec2((rect_.size.x / 2) - (text_size.x / 2), rect_.size.y / 3);
		text_ = std::make_unique<Label>(text, text_pos);
		text_->SetFont(font_);

		int y_pos =  (rect_.pos.y + rect_.size.y) - (rect_.size.y / 4);
		int height = rect_.pos.y + rect_.size.y - y_pos;
		button_container_ = std::make_unique<Container>(AABB(rect_.pos.x, y_pos, rect_.size.x, height), Container::Horizontal, 5, Alignment::VCenter | Alignment::HCenter);
		visible_ = false;
	}

	void Dialog::OnEvent(Event& event)
	{
		if (visible_){
			button_container_->OnEvent(event);
		}
	}

	void Dialog::Render() const
	{
		if (visible_){
			DrawQuad(rect_.pos, rect_.size, bg_color_);
			text_->Render();
			button_container_->Render();
		}
	}

	void Dialog::SetPos(Vec2 pos)
	{
		Vec2 offset = pos - rect_.pos;
		rect_.pos = pos;

		button_container_->SetPos(button_container_->GetRect().pos + offset);
		text_->SetPos(text_->GetRect().pos + offset);
	}

	void Dialog::AddButton(const std::string& label, std::function<void()> callback)
	{
		int button_width = rect_.size.x / 4;

		auto button = button_container_->AddWidget<Button>(AABB(0,0, button_width, button_container_->GetRect().size.y), label);
		button->ConnectSignal("pressed", [&visible = visible_, callback](){visible = false; callback();});
	}
}

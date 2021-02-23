#include "Dialog.h"

#include "../Renderer/Renderer.h"
#include "../Core/Application.h"

namespace Aegis{
	Dialog::Dialog(const std::string& text, const AABB& rect)
		:Widget(rect)
	{
		AddSignal("accepted");
		AddSignal("rejected");
		int button_width = rect_.size.x / 4;
		int button_height = rect_.size.y / 10;
		int button_y_pos = rect_.pos.y + rect_.size.x - button_height - 10;

		int accept_x_pos = rect_.pos.x + rect_.size.x / 4 - 10;
		int reject_x_pos = accept_x_pos + button_width + 10;
		accept_button_ = std::make_unique<Button>(AABB(accept_x_pos, button_y_pos, button_width, button_height), "Ok"); 
		reject_button_ = std::make_unique<Button>(AABB(reject_x_pos, button_y_pos, button_width, button_height), "Cancel");
		accept_button_->ConnectSignal("pressed", [&]() {visible_ = false; Emit("accepted");});
		reject_button_->ConnectSignal("pressed", [&]() {visible_ = false; Emit("rejected");});

		auto font = Application::GetFont();
		Vec2 text_size = font->GetStringPixelSize(text);
		Vec2 text_pos = rect_.pos + Vec2((rect_.size.x / 2) - (text_size.x / 2), rect_.size.y / 3);
		text_ = std::make_unique<Label>(text, text_pos);
		text_->SetFont(font);

		visible_ = false;
	}

	void Dialog::OnEvent(Event& event)
	{
		if (visible_){
			accept_button_->OnEvent(event);
			reject_button_->OnEvent(event);
		}
	}

	void Dialog::Render() const
	{
		if (visible_){
			DrawQuad(rect_.pos, rect_.size, { 0.309f, 0.517f, 0.811f, 1.0f});
			text_->Render();
			accept_button_->Render();
			reject_button_->Render();
		}
	}
}

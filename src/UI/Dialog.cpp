#include "Dialog.h"

#include "../Renderer/Renderer.h"
#include "../Application.h"

namespace Aegis{
	Dialog::Dialog(const std::string& text, Vec2 pos, Vec2 size)
		:pos_(pos), size_(size)
	{
		int button_width = size_.x / 4;
		int button_height = size_.y / 10;
		int button_y_pos = pos_.y + size_.x - button_height - 10;

		int accept_x_pos = pos_.x + size_.x / 4 - 10;
		int reject_x_pos = accept_x_pos + button_width + 10;
		accept_button_ = std::make_unique<Button>(AABB(accept_x_pos, button_y_pos, button_width, button_height), "Ok", [](){}); 
		reject_button_ = std::make_unique<Button>(AABB(reject_x_pos, button_y_pos, button_width, button_height), "Cancel", [](){});

		auto font = Application::GetFont();
		Vec2 text_size = font->GetStringPixelSize(text);
		Vec2 text_pos = pos_ + Vec2((size.x / 2) - (text_size.x / 2), size_.y / 3);
		text_ = std::make_unique<Label>(text, text_pos);
		text_->SetFont(font);
	}

	void Dialog::OnEvent(Event& event)
	{
		accept_button_->OnEvent(event);
		reject_button_->OnEvent(event);
	}

	void Dialog::Render()
	{
		DrawQuad(pos_, size_, { 0.309f, 0.517f, 0.811f, 1.0f});
		text_->Render();
		accept_button_->Render();
		reject_button_->Render();
	}

	void Dialog::SetAcceptedCallback(std::function<void()> callback)
	{
		accept_button_->callback_ = callback;
	}

	void Dialog::SetRejectedCallback(std::function<void()> callback)
	{
		reject_button_->callback_ = callback;
	}
}

#include "Dropdown.h"

#include "../Renderer/Renderer.h"
#include "../FontManager.h"

namespace Aegis {
	Dropdown::Dropdown(const std::string& label, Aegis::AABB rect)
	{
		button_pos_offset_ = FontManager::Instance().Load("assets/fonts/WorkSans-Regular.ttf", 32)->GetStringPixelWidth(label) + 15;
		pos_ = rect.pos;
		size_ = rect.size;
		label_ = label;
	}

	Dropdown::~Dropdown()
	{
	}

	void Dropdown::OnEvent(Event& event)
	{
		auto click = dynamic_cast<MouseClickEvent*>(&event);
		if (click){
			if (collapsed_) {
				if (items_[current_item_index_]->IsPressed(click->action_)) {
					collapsed_ = false;
				}
				return;
			}

			for (int i = 0; i < items_.size(); ++i) {
				if (items_[i]->IsPressed(click->action_)) {
					items_[i]->callback_();
					collapsed_ = true;
					SetCurrentIndex(i);
					return;
				}
			}

		}
	}

	void Dropdown::Render(float delta_time)
	{
		DrawText(label_, pos_, { 1.0f, 1.0f, 1.0f, 1.0f });

		if (collapsed_ && !items_.empty()) {
			items_[current_item_index_]->Render();
		}
		else {
			for (auto item : items_) {
				item->Render();
			}
		}
	}

	void Dropdown::AddItem(const std::string& text, std::function<void()> callback)
	{
		float y_pos = pos_.y + size_.y * items_.size();

		Button* temp_button = new Button({ pos_.x + button_pos_offset_, y_pos, size_.x, size_.y }, text, FontManager::Instance().Load("assets/fonts/WorkSans-Regular.ttf", 32), callback);
		items_.push_back(temp_button);
	}

	void Dropdown::MoveSelectedToTop(int index)
	{
		std::swap(items_[index]->rect_, items_[current_item_index_]->rect_);
	}
	void Dropdown::SetCurrentIndex(int index)
	{
		MoveSelectedToTop(index);
		current_item_index_ = index;
	}
}

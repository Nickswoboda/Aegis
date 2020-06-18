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
	}

	void Dropdown::Render(float delta_time)
	{
		DrawText(label_, pos_, { 1.0f, 1.0f, 1.0f, 1.0f });

		if (collapsed_ && !items_.empty()) {
			items_[0].Render();
		}
		else {
			for (auto item : items_) {
				item.Render();
			}
		}
	}

	void Dropdown::AddItem(const std::string& text, std::function<void()> callback)
	{
		float y_pos = pos_.y + size_.y * items_.size();

		Button* temp_button = new Button({ pos_.x + button_pos_offset_, y_pos, size_.x, size_.y }, text, FontManager::Instance().Load("assets/fonts/WorkSans-Regular.ttf", 32), callback);

	}

	bool Dropdown::IsPressed(int action)
	{
		if (collapsed_) {
			if (items_[0].IsPressed(action)) {
				collapsed_ = false;
				return true;
			}
			return false;
		}

		for (int i = 0; i < items_.size(); ++i) {
			if (items_[i].IsPressed(action)) {
				current_item_index_ = i;
				items_[i].callback_();
				collapsed_ = true;
				MoveSelectedToTop();
				return true;
			}
		}

		return false;
	}

	void Dropdown::MoveSelectedToTop()
	{
		items_[current_item_index_].rect_ = { pos_.x + button_pos_offset_, pos_.y, size_.x, size_.y };

		int num_item = 1;
		for (int i = 0; i < items_.size(); ++i) {
			if (i != current_item_index_) {
				float y_pos = pos_.y + size_.y * num_item;
				items_[i].rect_ = { pos_.x + button_pos_offset_, y_pos, size_.x, size_.y };
				++num_item;
			}
		}
	}
	void Dropdown::SetCurrentIndex(int index)
	{
		current_item_index_ = index;
		MoveSelectedToTop();
	}
}

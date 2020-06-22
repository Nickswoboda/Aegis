#include "Dropdown.h"

#include "../Renderer/Renderer.h"
#include "../FontManager.h"

namespace Aegis {
	Dropdown::Dropdown(const std::string& label, Aegis::AABB rect)
		:UIWidget(rect)
	{
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
		DrawText(label_, rect_.pos, { 1.0f, 1.0f, 1.0f, 1.0f });

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
		float y_pos = rect_.pos.y + rect_.size.y * items_.size();

		Button* temp_button = new Button({ rect_.pos.x + button_pos_offset_, y_pos, rect_.size.x, rect_.size.y }, text, callback);
		temp_button->SetFont(font_);
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

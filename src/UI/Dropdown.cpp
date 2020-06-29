#include "Dropdown.h"

#include "../Renderer/Renderer.h"
#include "../FontManager.h"

namespace Aegis {
	Dropdown::Dropdown(const std::string& label, Aegis::AABB rect)
		:Widget(rect)
	{
		button_pos_offset_ = Renderer2D::GetFont().GetStringPixelSize(label).x + 15;
		expand_button_ = new Button(rect, "", [&](){ToggleExpanded();});
		label_ = label;
	}

	Dropdown::~Dropdown()
	{
	}

	void Dropdown::OnEvent(Event& event)
	{
		expand_button_->OnEvent(event);
		if (expanded_){
			for (int i = 0; i < items_.size(); ++i) {
				items_[i]->OnEvent(event);
				if (items_[i]->pressed_){
					expanded_ = false;
					SetCurrentIndex(i);
					event.handled_ = true;
					return;
				}
			}
		}
	}

	void Dropdown::Render(float delta_time)
	{
		DrawText(label_, rect_.pos, { 1.0f, 1.0f, 1.0f, 1.0f });
		expand_button_->Render();
		if (!expanded_ && !items_.empty()) {
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

	void Dropdown::ToggleExpanded()
	{
		if (expanded_){
			expanded_ = false;
		}
		else{
			expanded_ = true;
		}
	}

	void Dropdown::SetFont(std::shared_ptr<Font>& font)
	{
		font_ = font;
		button_pos_offset_ = font->GetStringPixelSize(label_).x + 15;
		//must change button pos based off of new label size
		expand_button_->rect_.pos.x += button_pos_offset_;
		for (auto& button : items_){
			button->rect_.size.x = rect_.size.x + button_pos_offset_;
		}
	}
}

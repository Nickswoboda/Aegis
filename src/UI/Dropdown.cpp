#include "Dropdown.h"

#include "../Renderer/Renderer.h"
#include "../FontManager.h"
#include "../Application.h"
#include "../MouseCodes.h"

namespace Aegis {
	Dropdown::Dropdown(const std::string& label, Aegis::AABB rect)
		:Widget(rect)
	{
		label_offset_ = Renderer2D::GetFont().GetStringPixelSize(label).x + 15;
		label_ = label;
	}

	void Dropdown::OnEvent(Event& event)
	{
		auto click = dynamic_cast<MouseClickEvent*>(&event);

		if (click && click->action_ == AE_BUTTON_PRESS){
			Vec2 mouse_pos = Application::GetWindow().GetMousePos();
			if (PointInAABB(mouse_pos, rect_)){
				ToggleExpanded();
			}
			else if (expanded_){
				for (auto& item : items_) {
					if (PointInAABB(mouse_pos, item.rect_)){
						MoveToTop(item.id_);
						callbacks_[item.id_]();
						event.handled_ = true;
						expanded_ = false;
						return;
					}
				}
			}
		}
	}

	void Dropdown::Render(float delta_time)
	{
		Renderer2D::SetFont(font_);
		DrawText(label_, {rect_.pos.x - label_offset_, rect_.pos.y}, { 1.0f, 1.0f, 1.0f, 1.0f });

		if (!expanded_ && !items_.empty()) {
			auto curr_item = items_[current_item_index_];
			DrawQuad(curr_item.rect_.pos, curr_item.rect_.size, {0.2f, 0.2f, 1.0f, 1.0f});
			DrawStaticText(curr_item.text_, curr_item.rect_.pos);
		}
		else {
			for (auto item : items_) {
				DrawQuad(item.rect_.pos, item.rect_.size, {0.2f, 0.2f, 1.0f, 1.0f}, 1.0f);
				DrawStaticText(item.text_, item.rect_.pos, {1.0f, 1.0f, 1.0f, 1.0f}, 1.0f);
			}
		}
	}

	void Dropdown::AddItem(const std::string& text, std::function<void()> callback)
	{
		auto new_rect = rect_;
		new_rect.pos.y = rect_.pos.y + rect_.size.y * items_.size();

		Item item = { new_rect, text, items_.size() };

		items_.push_back(item);
		callbacks_.push_back(callback);
	}

	void Dropdown::MoveToTop(int id)
	{
		std::swap(items_[id].rect_, items_[current_item_index_].rect_);
		current_item_index_ = id;
	}

	void Dropdown::ToggleExpanded()
	{
		expanded_ = !expanded_;
	}

	void Dropdown::SetFont(std::shared_ptr<Font>& font)
	{
		font_ = font;
		label_offset_ = font->GetStringPixelSize(label_).x + 15;
	}
}

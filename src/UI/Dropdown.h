#pragma once

#include "Button.h"

#include <string>
#include <vector>
#include <functional>
#include <queue>

namespace Aegis {
	class Dropdown : public Widget
	{
	public:
		Dropdown(const std::string& label, AABB rect = {0,0,0,0});
		~Dropdown();

		void OnEvent(Event& event) override;
		void Render(float delta_time = 0.0f) override;
		void AddItem(const std::string& text, std::function<void()> callback);
		void MoveSelectedToTop(int index);
		void SetCurrentIndex(int index);
		void ToggleExpanded();
		void SetFont(std::shared_ptr<Font>& font) override;
		Button* expand_button_;
		std::vector<Button*> items_;

		int current_item_index_ = 0;
		std::string label_;
		bool expanded_ = false;
		int button_pos_offset_;
	};
}

#pragma once

#include "Button.h"

#include <string>
#include <functional>
#include <queue>

namespace Aegis {
	class Dropdown
	{
	public:
		Dropdown(const std::string& label, AABB rect);
		~Dropdown();

		void Render();
		void AddItem(const std::string& text, std::function<void()> callback);
		bool IsPressed(int action);
		void MoveSelectedToTop();
		void SetCurrentIndex(int index);


		Button* dropdown_button_ = nullptr;
		std::vector<std::pair<Button*, std::function<void()>>> items_;

		Vec2 pos_;
		Vec2 size_;
		int current_item_index_ = 0;
		std::string label_;
		bool collapsed_ = true;
		int button_pos_offset_;
	};
}
#pragma once

#include "Button.h"

#include <string>
#include <vector>
#include <functional>
#include <queue>

namespace Aegis {
	class Dropdown : public UIWidget
	{
	public:
		Dropdown(const std::string& label, AABB rect);
		~Dropdown();

		void OnEvent(Event& event) override;
		void Render(float delta_time = 0.0f) override;
		void AddItem(const std::string& text, std::function<void()> callback);
		bool IsPressed(int action);
		void MoveSelectedToTop();
		void SetCurrentIndex(int index);

		std::vector<Button> items_;


		Vec2 pos_;
		Vec2 size_;
		int current_item_index_ = 0;
		std::string label_;
		bool collapsed_ = true;
		int button_pos_offset_;
	};
}

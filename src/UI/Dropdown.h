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

		struct Item
		{
			AABB rect_;
			std::string text_;
			int id_;
		};

		Dropdown(const std::string& label);

		void OnEvent(Event& event) override;
		void Render() const override;
		void AddItem(const std::string& text, std::function<void()> callback);
		void MoveToTop(int id);
		void ToggleExpanded();
		void SetFont(std::shared_ptr<Font> font) override;

		std::vector<Item> items_;
		std::vector<std::function<void()>> callbacks_;
		int current_item_index_ = 0;
		std::string label_;
		bool expanded_ = false;
		int label_offset_ = 0;
	};
}

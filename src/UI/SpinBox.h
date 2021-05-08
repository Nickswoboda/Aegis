#pragma once

#include "Widget.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"

namespace Aegis{
	class SpinBox : public Widget
	{
	public:
		SpinBox();
		SpinBox(int value, int step);

		void OnEvent(Event& event) override;
		void Render() const override;

		void SetPos(Vec2 pos) override;
		void SetSize(Vec2 size) override;

		void SetFont(std::shared_ptr<Font> font) override;
		void SetValue(int value);
		int GetValue() const;
		void SetSuffix(const std::string& suffix);

		void SetButtonBorderSize(int size);
		void SetButtonStateBgColor(Button::State state, const Vec4& color);
		
		//replace with textinput once implemented
		std::shared_ptr<Label> value_label_;
		int border_size_ = 3;
		Vec4 bg_color_ = {0.0f, 0.0f, 0.8f, 1.0f};
		int min_value_ = 0;
		int max_value_ = std::numeric_limits<int>::max();

	private:

		void ResizeComponents();
		VContainer button_box_;
		std::shared_ptr<Button> plus_button_;
		std::shared_ptr<Button> minus_button_;

		std::string suffix_;
		Vec4 border_color_ = {0.0f, 0.0f, 0.0f, 1.0f};
		int value_ = 0;
		int step_ = 1;
	};
}

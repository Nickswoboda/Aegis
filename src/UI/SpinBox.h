#pragma once

#include "Widget.h"
#include "Container.h"
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

		void SetValue(int value);
		int GetValue() const;

		std::shared_ptr<Container> button_box_;
		
		//replace with textinput once implemented
		std::shared_ptr<Label> value_label_;

	private:
		Vec4 bg_color_ = {0.0f, 0.0f, 0.8f, 1.0f};
		Vec2 bg_size_ = {75, 25};
		int value_ = 0;
		int min_value_ = 0;
		int max_value_ = std::numeric_limits<int>::max();
		int step_ = 1;
	};
}

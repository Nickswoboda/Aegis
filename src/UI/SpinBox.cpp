#include "SpinBox.h"

#include "Button.h"
#include "../Renderer/Renderer.h"

namespace Aegis {
	SpinBox::SpinBox(int value, int step)
		:Widget({0, 0, 100, 25}), step_(step)
	{
		button_box_ = std::make_shared<Container>(AABB(75, 0, 25, 25), Container::Vertical, 1);
		auto plus_button = button_box_->AddWidget<Button>(AABB(0, 0, 25, 10), "+");
		auto minus_button = button_box_->AddWidget<Button>(AABB(0, 0, 25, 10), "-");
		value_label_ = std::make_shared<Label>("", Vec2{0,0});
		SetValue(value);

		plus_button->ConnectSignal("pressed", [&](){SetValue(value_ + step_);});
		minus_button->ConnectSignal("pressed", [&](){SetValue(value_ - step_);});
	}

	SpinBox::SpinBox()
		:SpinBox(0, 1)
	{ }

	void SpinBox::OnEvent(Event& event)
	{
		button_box_->OnEvent(event);
	}
	void SpinBox::Render() const
	{
		button_box_->Render();
		DrawQuad(rect_.pos, {75, 25}, bg_color_);
		value_label_->Render();
	}

	void SpinBox::SetPos(Vec2 pos)
	{
		Vec2 offset = pos - rect_.pos;
		rect_.pos = pos;

		button_box_->SetPos(button_box_->GetRect().pos + offset);
		value_label_->SetPos(value_label_->GetRect().pos + offset);
	};

	void SpinBox::SetValue(int value)
	{
		value_ = value > max_value_ ? max_value_ : (value < min_value_ ? min_value_ : value);
		value_label_->SetText(std::to_string(value_));

		AABB label_rect = value_label_->GetRect();
		AABB bg_rect = {rect_.pos, bg_size_}; 
		CenterAABB(label_rect, bg_rect);
		value_label_->SetPos(label_rect.pos);
	}

	int SpinBox::GetValue() const
	{
		return value_;
	}

}

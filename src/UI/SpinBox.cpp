#include "SpinBox.h"

#include "Button.h"
#include "../Renderer/Renderer.h"

namespace Aegis {
	SpinBox::SpinBox(int value, int step)
		: step_(step)
	{
		AddSignal("value changed");

		button_box_.SetPos({75, 0});
		button_box_.SetSize({50, 50});
		button_box_.SetPadding(0);

		plus_button_ = button_box_.AddWidget<Button>("+");
		plus_button_->SetSize({ 25, 10 });
		minus_button_ = button_box_.AddWidget<Button>( "-");
		minus_button_->SetSize({ 25, 10 });
		value_label_ = std::make_shared<Label>("", Vec2{0,0});
		SetValue(value);

		plus_button_->ConnectSignal("pressed", [&](){SetValue(value_ + step_); Emit("value changed");});
		minus_button_->ConnectSignal("pressed", [&](){SetValue(value_ - step_); Emit("value changed");});

		ResizeComponents();
		SetSize({ 100, 25 });
	}

	SpinBox::SpinBox()
		:SpinBox(0, 1)
	{ }

	void SpinBox::OnEvent(Event& event)
	{
		button_box_.OnEvent(event);
	}
	void SpinBox::Render() const
	{
		DrawQuad(rect_.pos, rect_.size, bg_color_);
		button_box_.Render();
		value_label_->Render();

		if (border_size_ > 0){
			Aegis::DrawQuad(rect_.pos, Vec2(border_size_, rect_.size.y), border_color_);
			Aegis::DrawQuad(rect_.pos + Vec2{rect_.size.x - border_size_, 0}, Vec2(border_size_, rect_.size.y), border_color_);
			Aegis::DrawQuad(rect_.pos + Vec2{0, rect_.size.y - border_size_}, Vec2(rect_.size.x, border_size_), border_color_);
			Aegis::DrawQuad(rect_.pos, Vec2(rect_.size.x, border_size_), border_color_);
		}
	}

	void SpinBox::SetPos(Vec2 pos)
	{
		Vec2 offset = pos - rect_.pos;
		rect_.pos = pos;

		button_box_.SetPos(button_box_.GetRect().pos + offset);
		value_label_->SetPos(value_label_->GetRect().pos + offset);
	};

	void SpinBox::SetSize(Vec2 size)
	{
		rect_.size = size;
		ResizeComponents();
		Emit("size changed");
	}

	void SpinBox::SetFont(std::shared_ptr<Font> font)
	{
		font_ = font;
		value_label_->SetFont(font);
		SetValue(value_);
	}

	void SpinBox::ResizeComponents()
	{
		Aegis::Vec2 box_size;
		box_size.x = rect_.size.x / 4;
		box_size.y = rect_.size.y - (border_size_ + 1) * 2;
		button_box_.SetSize(box_size);

		int box_x_pos = rect_.pos.x + rect_.size.x - box_size.x - border_size_; 
		int height_diff = rect_.size.y - box_size.y;
		int box_y_pos = rect_.pos.y + (height_diff / 2);
		button_box_.SetPos(Vec2(box_x_pos, box_y_pos));

		int button_height = (box_size.y - button_box_.GetPadding()) / 2;

		button_box_.SetSize(Vec2(box_size.x, rect_.size.y));
		plus_button_->SetSize(Vec2(box_size.x, button_height));
		minus_button_->SetSize(Vec2(box_size.x, button_height));
		
		SetValue(value_);

	}

	void SpinBox::SetValue(int value)
	{
		value_ = value > max_value_ ? max_value_ : (value < min_value_ ? min_value_ : value);
		value_label_->SetText(std::to_string(value_) + suffix_);

		AABB label_rect = value_label_->GetRect();
		AABB label_bg_rect = {rect_.pos, rect_.size - Vec2(button_box_.GetRect().size.x, 0)};
		CenterAABB(label_rect, label_bg_rect);
		value_label_->SetPos(label_rect.pos);
	}

	int SpinBox::GetValue() const
	{
		return value_;
	}

	void SpinBox::SetButtonBorderSize(int size)
	{
		plus_button_->border_size_ = size;
		minus_button_->border_size_ = size;
	}

	void SpinBox::SetButtonStateBgColor(Button::State state, const Vec4& color)
	{
		plus_button_->SetStateBgColor(state, color);
		minus_button_->SetStateBgColor(state, color);
	}

	void SpinBox::SetSuffix(const std::string& suffix)
	{
		suffix_ = suffix;
		SetValue(value_);
	}
}

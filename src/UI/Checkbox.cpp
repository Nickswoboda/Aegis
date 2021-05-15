#include "Checkbox.h"

#include "../Renderer/Renderer.h"

namespace Aegis{
	Checkbox::Checkbox(const std::string& label)
	{
		button_ = h_box_.AddWidget<Button>();
		label_ = h_box_.AddWidget<Label>(label, Aegis::Vec2());
		SetSize({ 100, 50 });

		AddSignal("checked");
		AddSignal("unchecked");

		h_box_.SetSize(rect_.size);
		h_box_.SetPadding(8);
		h_box_.SetAlignment(Alignment::Center);

		button_->SetSize({ 25,25 });
		button_->ConnectSignal("pressed", [&]() {
				SetState(!checked_);
			});
		button_->border_size_ = 3;

		UpdateHBoxSize();

		colors_[0] = {1.0f, 1.0f, 1.0f, 1.0f};
		colors_[1] = {0.3f, 0.3f, 0.3f, 1.0f};
		UpdateButtonTexture();
	}

	void Checkbox::OnEvent(Event& event)
	{
		button_->OnEvent(event);
	}

	void Checkbox::Render() const
	{
		if (!visible_) return;

		h_box_.Render();
	}

	void Checkbox::SetFont(std::shared_ptr<Font> font)
	{
		font_ = font;
		label_->SetFont(font_);
		UpdateHBoxSize();
	}

	void Checkbox::SetPos(Vec2 pos)
	{
		rect_.pos = pos;
		h_box_.SetPos(pos);
	}

	void Checkbox::SetSize(Vec2 size)
	{
		button_->SetSize(size);
		UpdateHBoxSize();
	}

	void Checkbox::SetText(const std::string& text)
	{
		label_->SetText(text);
		UpdateHBoxSize();
	}

	void Checkbox::SetState(bool checked)
	{
		checked_ = checked; 
		UpdateButtonTexture();
		Emit(checked_ ? "checked" : "unchecked");
	}

	void Checkbox::UpdateHBoxSize()
	{
		Vec2 new_size;
		Vec2 button_size = button_->GetRect().size;
		Vec2 text_size = label_->GetRect().size;

		new_size.y = std::max(button_size.y, text_size.y);
		new_size.x = button_size.x + text_size.x + (h_box_.GetPadding()*3);

		h_box_.SetSize(new_size);
		rect_.size = new_size;
		Emit("size changed");
	}
	void Checkbox::SetStateTexture(bool checked, std::shared_ptr<Texture> texture)
	{
		if (texture){
			textures_[checked] = texture;
		}

		UpdateButtonTexture();
	}

	void Checkbox::SetStateColor(bool checked, const Vec4& color)
	{
		colors_[checked] = color;
		UpdateButtonTexture();
	}

	void Checkbox::UpdateButtonTexture()
	{
		if (textures_[checked_]){
			button_->SetStateTexture(Button::Normal, textures_[checked_]); 
			button_->SetStateTexture(Button::Hovered, textures_[checked_]); 
			button_->SetStateTexture(Button::Pressed, textures_[checked_]); 
		} else {
			button_->SetStateTexture(Button::Normal, {}); 
			button_->SetStateTexture(Button::Hovered, {}); 
			button_->SetStateTexture(Button::Pressed, {}); 

			button_->SetStateBgColor(Button::Normal, colors_[checked_]); 
			button_->SetStateBgColor(Button::Hovered, colors_[checked_]); 
			button_->SetStateBgColor(Button::Pressed, colors_[checked_]); 
		}
	}
}

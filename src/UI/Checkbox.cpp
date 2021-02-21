#include "Checkbox.h"

#include "../Renderer/Renderer.h"

namespace Aegis{
	Checkbox::Checkbox(const std::string& label, AABB box)
		:Widget(box), label_(label)
	{
		AddSignal("checked");
		AddSignal("unchecked");

		button_ = std::make_unique<Button>(box, "");
		button_->ConnectSignal("pressed", [&]() { checked_ = !checked_; Emit(checked_ ? "checked" : "unchecked");});
	}

	void Checkbox::OnEvent(Event& event)
	{
		button_->OnEvent(event);
	}

	void Checkbox::Render() const
	{
		Renderer2D::SetFont(font_);
		if (textures_[checked_]){
			DrawQuad(rect_.pos, rect_.size, *textures_[checked_]);
		} else {
			auto color = checked_ ? Aegis::Vec4(0.2f, 0.2f, 0.2f, 1.0f) : Aegis::Vec4(0.8f, 0.8f, 0.2f, 1.0f);
			DrawQuad(rect_.pos, rect_.size, color, z_idx_);
		}
		DrawText(label_, {rect_.pos.x - label_offset_, rect_.pos.y});
	}


	void Checkbox::SetFont(std::shared_ptr<Font> font)
	{
		font_ = font;

		label_offset_ = font_->GetStringPixelSize(label_).x + 20;
	}

	void Checkbox::SetTexture(bool checked, std::shared_ptr<Texture> texture)
	{
		if (texture){
			textures_[checked] = texture;
		}
	}
}

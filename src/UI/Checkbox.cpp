#include "Checkbox.h"

#include "../Renderer/Renderer.h"

namespace Aegis{
	Checkbox::Checkbox(const std::string& label, AABB box, std::function<void(bool)> callback)
		:Widget(box), label_(label), callback_(callback)
	{
		button_ = new Button(box, "", [&](){
			if (checked_){
				checked_ = false;
			}
			else{
				checked_ = true;
			}

			callback_(checked_);});
	}

	void Checkbox::OnEvent(Event& event)
	{
		button_->OnEvent(event);
	}

	void Checkbox::Render(float delta_time)
	{
		Renderer2D::SetFont(font_);
		button_->Render(delta_time);
		if (textures_[checked_]){
			DrawQuad(rect_.pos, rect_.size, textures_[checked_]);
		}
		DrawText(label_, {rect_.pos.x - label_offset_, rect_.pos.y});
		
	}


	void Checkbox::SetFont(std::shared_ptr<Font>& font)
	{
		font_ = font;

		label_offset_ = font_->GetStringPixelSize(label_).x + 20;
	}

	void Checkbox::SetTexture(bool checked, std::shared_ptr<Texture>& texture)
	{
		if (texture){
			textures_[checked] = texture;
		}
	}
}

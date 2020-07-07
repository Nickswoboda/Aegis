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
		if (checked_) {
			DrawText("CHECKED", rect_.pos);
		}
		DrawText(label_, {rect_.pos.x - label_offset_, rect_.pos.y});
		
	}


	void Checkbox::SetFont(std::shared_ptr<Font>& font)
	{
		font_ = font;

		label_offset_ = font_->GetStringPixelSize(label_).x + 20;
	}
}

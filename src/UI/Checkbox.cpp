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
		DrawText(label_, rect_.pos);
		button_->Render(delta_time);
		
	}


}

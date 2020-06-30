#pragma once 

#include "Widget.h"
#include "Button.h"

#include <string>

namespace Aegis{

	class Checkbox : public Widget
	{
	public:
		Checkbox(const std::string& label, AABB box, std::function<void(bool)> callback);
		void OnEvent(Event& event) override;
		void Render(float delta_time) override;

		std::string label_;
		Button* button_;
		bool checked_ = false;
		std::function<void(bool)> callback_;
	};
}

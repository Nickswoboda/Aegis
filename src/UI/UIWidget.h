#pragma once

#include "../Event.h"
namespace Aegis {

	class UIWidget
	{
	public:
		virtual void OnEvent(Event& event) = 0;
		virtual void Render(float delta_time) = 0;
	};
}

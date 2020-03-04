#pragma once

#include "Event.h"
namespace Aegis {

	class Layer
	{
	public:
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};
	};
}
#pragma once

#include "Window.h"
#include "Event.h"

namespace Aegis {

	class Application
	{
	public:
		Application(int width, int height);
		~Application();

		void Run();
		void OnEvent(Event& event);
		void OnWindowClose();
	private:
		Window* window_ = nullptr;

		bool running_ = true;
	};
}
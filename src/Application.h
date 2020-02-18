#pragma once

#include "Window.h"

namespace Aegis {

	class Application
	{
	public:
		Application(int width, int height);
		~Application();

		void Run();
		bool OnWindowClose();
	private:
		Window* window_ = nullptr;

		bool running_ = true;
	};
}
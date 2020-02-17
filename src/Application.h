#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Aegis {

	class Application
	{
	public:
		Application(int width, int height);
		~Application();

		void Run();

		GLFWwindow* window_ = nullptr;
	};
}
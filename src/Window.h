#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <functional>
namespace Aegis {
	class Window
	{
	public:
		Window(const std::string& title, int width, int height);
		~Window();

		void SetEventCallbacks();
		void OnUpdate();

		std::function<bool()> callback_;
	private:
		GLFWwindow* window_;
	};
}
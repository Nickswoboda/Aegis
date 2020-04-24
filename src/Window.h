#pragma once

#include "Event.h"

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
		void SetSize(int width, int height);
		void OnUpdate();
		GLFWwindow* GetWindowHandle() { return window_; };
		
		std::function<void(Event&)> callback_;
		int width_;
		int height_;
	private:
		GLFWwindow* window_;
	};
}
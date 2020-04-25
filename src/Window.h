#pragma once

#include "Event.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <functional>
namespace Aegis {

	enum class ScreenMode
	{
		Fullscreen,
		Windowed,
		FullscreenWindow
	};
	class Window
	{
	public:
		Window(const std::string& title, int width, int height);
		~Window();

		void SetEventCallbacks();
		void SetScreenMode(ScreenMode screen_mode);
		void OnUpdate();
		GLFWwindow* GetWindowHandle() { return window_; };
		
		std::function<void(Event&)> callback_;
		int width_;
		int height_;
		ScreenMode screen_mode_ = ScreenMode::Windowed;
	private:
		GLFWwindow* window_;
	};
}
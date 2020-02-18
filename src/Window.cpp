#include "Window.h"

#include <iostream>

namespace Aegis {

	Window::Window(const std::string& title, int width, int height)
	{
		window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window_ == nullptr) {
			std::cout << "Unable to create window";
		}

		glfwMakeContextCurrent(window_);
		glfwSetWindowUserPointer(window_, &callback_);
		SetEventCallbacks();
	}

	Window::~Window()
	{
	}

	void Window::SetEventCallbacks()
	{
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			std::cout << "Resize: " << width << ", " << height << "\n";
		});
		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_();
		});
		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			std::cout << "Key: " << key << ", " << scancode << ", " << action << ", " << mods << "\n";
		});
		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x_pos, double y_pos) {
			std::cout << "Cursor Pos: " << x_pos << ", " << y_pos << "\n";
		});
		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			std::cout << "Mouse Button" << button << ", " << action << ", " << mods << "\n";
		});
		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset) {
			std::cout << "Scroll: " << xoffset << ", " << yoffset << "\n";
		});
	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}
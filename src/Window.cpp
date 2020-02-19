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
		glfwSetWindowUserPointer(window_, (void*)this);
		SetEventCallbacks();
	}

	Window::~Window()
	{
	}

	void Window::SetEventCallbacks()
	{
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_(WindowResizeEvent(width, height));
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_(WindowCloseEvent());
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_(KeyEvent(key, scancode, action, mods));
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x_pos, double y_pos) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_(MouseMoveEvent(x_pos, y_pos));
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_(MouseClickEvent(button, action, mods));
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			window_handle.callback_(MouseScrollEvent(xoffset, yoffset));
		});
	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}
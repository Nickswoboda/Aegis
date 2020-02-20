#include "Window.h"

#include <glad/glad.h>

#include <iostream>

namespace Aegis {

	Window::Window(const std::string& title, int width, int height)
	{
		window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window_ == nullptr) {
			std::cout << "Unable to create window";
		}
		glfwMakeContextCurrent(window_);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Unable to initialize GLAD";
		}

		glfwSetWindowUserPointer(window_, (void*)this);
		SetEventCallbacks();

		glViewport(0, 0, width, height);
	}

	Window::~Window()
	{
	}

	void Window::SetEventCallbacks()
	{
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			window_handle.callback_(event);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			window_handle.callback_(event);
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			KeyEvent event(key, scancode, action, mods);
			window_handle.callback_(event);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x_pos, double y_pos) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event(x_pos, y_pos);
			window_handle.callback_(event);
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			MouseClickEvent event(button, action, mods);
			window_handle.callback_(event);
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event(xoffset, yoffset);
			window_handle.callback_(event);
		});

		glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});
	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}
}
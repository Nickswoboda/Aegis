#include "Window.h"

#include <glad/glad.h>

#include <iostream>

namespace Aegis {

	Window::Window(const std::string& title, int width, int height)
		:width_(width), height_(height)
	{
		window_handle_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window_handle_ == nullptr) {
			std::cout << "Unable to create window";
		}
		glfwMakeContextCurrent(window_handle_);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Unable to initialize GLAD";
		}

		glfwSetWindowUserPointer(window_handle_, (void*)this);
		resolution_ = { (float)width, (float)height };
		glViewport(0, 0, width, height);
	}

	Window::~Window()
	{
	}

	void Window::SetEventCallbacks(std::function<void(Event&)> callback)
	{
		callback_ = callback;

		glfwSetWindowSizeCallback(window_handle_, [](GLFWwindow* window, int width, int height) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			window_handle.callback_(event);
		});

		glfwSetWindowCloseCallback(window_handle_, [](GLFWwindow* window) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			window_handle.callback_(event);
		});

		glfwSetKeyCallback(window_handle_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			KeyEvent event(key, scancode, action, mods);
			window_handle.callback_(event);
		});

		glfwSetCursorPosCallback(window_handle_, [](GLFWwindow* window, double x_pos, double y_pos) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event(x_pos, y_pos);
			window_handle.callback_(event);
		});

		glfwSetMouseButtonCallback(window_handle_, [](GLFWwindow* window, int button, int action, int mods) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			MouseClickEvent event(button, action, mods);
			window_handle.callback_(event);
		});

		glfwSetScrollCallback(window_handle_, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window& window_handle = *(Window*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event(xoffset, yoffset);
			window_handle.callback_(event);
		});

		glfwSetFramebufferSizeCallback(window_handle_, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});
	}

	void Window::SetScreenMode(ScreenMode screen_mode)
	{

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vid = glfwGetVideoMode(monitor);

		switch (screen_mode)
		{
			case ScreenMode::Fullscreen: {
				screen_mode_ = ScreenMode::Fullscreen;
				glfwSetWindowMonitor(window_handle_, monitor, 0, 0, vid->width, vid->height, vid->refreshRate); break;
			}
			case ScreenMode::Windowed: {
				screen_mode_ = ScreenMode::Windowed;
				glfwSetWindowMonitor(window_handle_, nullptr, 50, 50, width_, height_, vid->refreshRate); break;
			}
			case ScreenMode::FullscreenWindow: {
				screen_mode_ = ScreenMode::FullscreenWindow;
				glfwSetWindowMonitor(window_handle_, monitor, 0, 0, vid->width, vid->height, vid->refreshRate); break;
			}
		}
	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(window_handle_);
		glfwPollEvents();
	}

	void Window::OnResize(const WindowResizeEvent& event)
	{
		glViewport(0, 0, event.width_, event.height_);

		width_ = event.width_;
		height_ = event.height_;

		mouse_pos_scale_ = resolution_ / Vec2(width_, height_);
		
	}

	void Window::SetVsync(bool vsync)
	{
		if (vsync && !IsVsync()) {
			glfwSwapInterval(1);
			vsync_ = true;
		}
		else if (!vsync && IsVsync()) {
			glfwSwapInterval(0);
			vsync_ = false;
		}
	}

	void Window::SetResolution(int x, int y)
	{
		resolution_ = Vec2(x, y);

		mouse_pos_scale_ = resolution_ / Vec2(width_, height_);
	}

	Vec2 Window::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(window_handle_, &x, &y);

		return Vec2(x, y) * mouse_pos_scale_;
	}
}
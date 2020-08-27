#include "Window.h"

#include "Assert.h"
#include <glad/glad.h>

#include <iostream>

namespace Aegis {

	Window::Window(const std::string& title, int width, int height, int flags)
		:size_{width, height}
	{
		window_handle_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		
		AE_ASSERT(window_handle_, "Unable to create window");
		glfwMakeContextCurrent(window_handle_);


		AE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Unable to initialize GLAD");

		glfwSetWindowUserPointer(window_handle_, (void*)this);

		resolution_ = { (float)width, (float)height };
		glViewport(0, 0, width, height);

		if (flags & WindowFlag_Centered) {
			CenterOnScreen();
		}
		if (flags & WindowFlag_NonResizable){
			glfwSetWindowAttrib(window_handle_, GLFW_RESIZABLE, GLFW_FALSE);
		}
		if (flags & WindowFlag_Undecorated) {
			glfwSetWindowAttrib(window_handle_, GLFW_DECORATED, GLFW_FALSE);
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(window_handle_);
	}

	void Window::SetEventCallbacks(std::function<void(Event&)> callback)
	{
		callback_ = callback;

		glfwSetWindowSizeCallback(window_handle_, [](GLFWwindow* window, int width, int height) {
			Window& window_handle = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			WindowResizeEvent event(width, height);
			window_handle.callback_(event);
		});

		glfwSetWindowCloseCallback(window_handle_, [](GLFWwindow* window) {
			Window& window_handle = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			window_handle.callback_(event);
		});

		glfwSetKeyCallback(window_handle_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window& window_handle = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			KeyEvent event(key, scancode, action, mods);
			window_handle.callback_(event);
		});

		glfwSetCursorPosCallback(window_handle_, [](GLFWwindow* window, double x_pos, double y_pos) {
			Window& window_handle = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			MouseMoveEvent event(x_pos, y_pos);
			window_handle.callback_(event);
		});

		glfwSetMouseButtonCallback(window_handle_, [](GLFWwindow* window, int button, int action, int mods) {
			Window& window_handle = *static_cast<Window*>(glfwGetWindowUserPointer(window));
			MouseClickEvent event(button, action, mods);
			window_handle.callback_(event);
		});

		glfwSetScrollCallback(window_handle_, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window& window_handle = *static_cast<Window*>(glfwGetWindowUserPointer(window));
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
				glfwSetWindowMonitor(window_handle_, nullptr, pos_.x, pos_.y, windowed_size_.x, windowed_size_.y, vid->refreshRate);

				//cache window pos for when returning to windowed mode
				int window_x, window_y;
				glfwGetWindowPos(window_handle_, &window_x, &window_y);
				pos_ = Vec2(window_x, window_y);  break;
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

	void Window::CenterOnScreen()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		int monitor_x, monitor_y;
		glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitor_x, &monitor_y);

		int window_width, window_height;
		glfwGetWindowSize(window_handle_, &window_width, &window_height);
		windowed_size_ = Vec2(window_width, window_height);

		glfwSetWindowPos(window_handle_,
			monitor_x + (mode->width - window_width) / 2,
			monitor_y + (mode->height - window_height) / 2);

		int window_x, window_y;
		glfwGetWindowPos(window_handle_, &window_x, &window_y);
		pos_ = Vec2(window_x, window_y);
	}

	void Window::SetPos(int x, int y)
	{
		glfwSetWindowPos(window_handle_, x, y);
	}

	Vec2 Window::GetPos()
	{
		return size_;
	}

	void Window::SetSize(int x, int y)
	{
		glfwSetWindowSize(window_handle_, x, y);
		windowed_size_ = Vec2(x, y);
	}

	Vec2 Window::GetSize()
	{
		return size_;
	}

	void Window::OnResize(const WindowResizeEvent& event)
	{
		glViewport(0, 0, event.width_, event.height_);

		size_ = Vec2(event.width_, event.height_);

		if (screen_mode_ == ScreenMode::Windowed) {
			windowed_size_ = Vec2(event.width_, event.height_);
		}

		mouse_pos_scale_ = resolution_ / size_;
		
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

		mouse_pos_scale_ = resolution_ / size_;
	}

	void Window::SetResizable(bool resizable)
	{
		glfwSetWindowAttrib(window_handle_, GLFW_RESIZABLE, resizable);
	}

	bool Window::IsResizable()
	{
		return glfwGetWindowAttrib(window_handle_, GLFW_RESIZABLE);
	}

	void Window::SetDecorated(bool decorated)
	{
		glfwSetWindowAttrib(window_handle_, GLFW_DECORATED, decorated);
	}

	bool Window::IsDecorated()
	{
		return glfwGetWindowAttrib(window_handle_, GLFW_DECORATED);
	}

	Vec2 Window::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(window_handle_, &x, &y);

		return Vec2(x, y) * mouse_pos_scale_;
	}
	
	bool Window::IsMousePressed()
	{
		return (glfwGetMouseButton(window_handle_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	}
}

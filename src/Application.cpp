#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Aegis {
	Application::Application(int width, int height)
	{
		if (!glfwInit()) {
			std::cout << "Unable to initiate GLFW";
			return;
		}

		window_ = new Window("Aegis", width, height);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Unable to initialize GLAD";
		}

		window_->callback_ = std::bind(&Application::OnEvent, this, std::placeholders::_1);
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		while (running_) {
			glClearColor(0.5, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			window_->OnUpdate();
		}
	}
	void Application::OnEvent(Event& event)
	{
		auto close_event = dynamic_cast<WindowCloseEvent*>(&event);
		if (close_event) {
			OnWindowClose();
			std::cout << "Closed" << "\n";
			return;
		}

		auto resize_event = dynamic_cast<WindowResizeEvent*>(&event);
		if (resize_event) {
			std::cout << "Resized" << "\n";
			return;
		}

		auto mouse_move = dynamic_cast<MouseMoveEvent*>(&event);
		if (mouse_move) {
			std::cout << "Mouse Moved" << "\n";
			return;
		}

		auto mouse_scroll = dynamic_cast<MouseScrollEvent*>(&event);
		if (mouse_scroll) {
			std::cout << "Mouse Scrolled" << "\n";
			return;
		}

		auto mouse_click = dynamic_cast<MouseClickEvent*>(&event);
		if (mouse_click) {
			std::cout << "Mouse Clicked" << "\n";
			return;
		}

		auto key = dynamic_cast<KeyEvent*>(&event);
		if (key) {
			std::cout << "Key" << "\n";
			return;
		}
	}

	void Application::OnWindowClose()
	{
		running_ = false;
	}
}
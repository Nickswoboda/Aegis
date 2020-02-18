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


		window_->callback_ = std::bind(&Application::OnWindowClose, this);
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
	bool Application::OnWindowClose()
	{
		running_ = false;
		return true;
	}
}
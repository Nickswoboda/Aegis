#include "Application.h"

#include <glad/glad.h>
#include <iostream>

namespace Aegis {
	Application::Application(int width, int height)
	{
		if (!glfwInit()) {
			std::cout << "Unable to initiate GLFW";
			return;
		}

		window_ = glfwCreateWindow(width, height, "Aegis", NULL, NULL);
		if (window_ == nullptr) {
			std::cout << "Unable to create window";
			glfwTerminate();
		}

		glfwMakeContextCurrent(window_);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Unable to initialize GLAD";
		}
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(window_)) {
			glClearColor(0.5, 0.0, 0.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window_);
			glfwPollEvents();
		}
	}
}
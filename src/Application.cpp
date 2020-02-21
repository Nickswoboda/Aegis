#include "Application.h"

#include "Renderer.h"

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

		window_ = std::make_unique<Window>("Aegis", width, height);
		window_->callback_ = std::bind(&Application::OnEvent, this, std::placeholders::_1);

		Renderer2D::Init();
		Renderer2D::SetClearColor(1.0, 0.5, 0.5, 1);

		vertex_array_ = std::make_unique<VertexArray>();
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		vertex_array_->Unbind();
		while (running_) {
			Renderer2D::Clear();
			Renderer2D::DrawQuad(1, 2, 3, 4);
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
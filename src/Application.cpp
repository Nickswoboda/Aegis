#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Font.h"

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
		Renderer2D::SetClearColor(0.2, 0.2, 0.6, 1);

		font_ = std::make_unique<Font>("assets/fonts/WorkSans-Regular.ttf", 16);
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		while (running_) {
			window_->OnUpdate();
			
			for (auto& layer : layers_) {
				layer->OnUpdate();
			}
		}
	}
	void Application::OnEvent(Event& event)
	{
		auto close_event = dynamic_cast<WindowCloseEvent*>(&event);
		if (close_event) {
			OnWindowClose();
			return;
		}

		auto resize_event = dynamic_cast<WindowResizeEvent*>(&event);
		if (resize_event) {
			return;
		}

		auto mouse_move = dynamic_cast<MouseMoveEvent*>(&event);
		if (mouse_move) {
			return;
		}

		auto mouse_scroll = dynamic_cast<MouseScrollEvent*>(&event);
		if (mouse_scroll) {
			return;
		}

		auto mouse_click = dynamic_cast<MouseClickEvent*>(&event);
		if (mouse_click) {
			return;
		}

		auto key = dynamic_cast<KeyEvent*>(&event);
		if (key) {
			return;
		}
	}

	void Application::OnWindowClose()
	{
		running_ = false;
	}
	void Application::PushLayer(Layer* layer)
	{
		layers_.emplace_back(std::move(layer));
	}
}	
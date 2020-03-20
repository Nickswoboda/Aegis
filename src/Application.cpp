#include "Application.h"

#include "Renderer/Renderer.h"
#include "Font.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

namespace Aegis {

	double Application::frame_time_ms_ = 0.0;

	Application::Application(int width, int height)
	{
		if (!glfwInit()) {
			std::cout << "Unable to initiate GLFW.\n";
			return;
		}

		window_ = std::make_unique<Window>("Aegis", width, height);
		window_->callback_ = std::bind(&Application::OnEvent, this, std::placeholders::_1);

		Renderer2D::Init();
	}

	Application::~Application()
	{
		Renderer2D::Shutdown();
		glfwTerminate();
	}

	void Application::Run()
	{
		while (running_) {
			auto begin_frame_time_ = std::chrono::high_resolution_clock::now();
			window_->OnUpdate();
			
			Renderer2D::BeginBatch();
			for (auto& layer : layers_) {
				layer->OnUpdate();
			}
			Renderer2D::EndBatch();

			auto end_frame_time_ = std::chrono::high_resolution_clock::now();
			frame_time_ms_ = std::chrono::duration<double, std::milli>(end_frame_time_ - begin_frame_time_).count();
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
			OnWindowResize(*resize_event);
		}

		if (!event.handled_) {
			for (auto& layer : layers_) {
				layer->OnEvent(event);
			}
		}
	}

	void Application::OnWindowClose()
	{
		running_ = false;
	}
	void Application::OnWindowResize(const WindowResizeEvent& event)
	{
		glViewport(0, 0, event.width_, event.height_);
		Renderer2D::SetProjection(event.width_, event.height_);
	}
	void Application::PushLayer(Layer* layer)
	{
		layers_.emplace_back(std::move(layer));
	}
	void Application::SetVsync(bool vsync)
	{
		if (vsync) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
	}
	double Application::GetFrameTime()
	{
		return frame_time_ms_;
	}
}	
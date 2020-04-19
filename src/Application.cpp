#include "Application.h"

#include "Renderer/Renderer.h"
#include "Font.h"
#include "Timer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>

namespace Aegis {

	double Application::frame_time_ms_ = 0.0;
	Application* Application::instance_ = nullptr;

	Application::Application(int width, int height)
	{
		if (instance_) {
			std::cout << "Application already created\n";
		}
		instance_ = this;
		if (!glfwInit()) {
			std::cout << "Unable to initiate GLFW.\n";
			return;
		}

		window_ = std::make_unique<Window>("Aegis", width, height);
		window_->callback_ = std::bind(&Application::OnEvent, this, std::placeholders::_1);

		Renderer2D::Init(width, height);
	}

	Application::~Application()
	{
		Renderer2D::Shutdown();
		glfwTerminate();
	}

	void Application::Run()
	{

		float MS_PER_UPDATE = 16.66666;
		Timer timer;
		timer.Start();
		double accumulator_ = 0.0;
		while (running_) {

			timer.Update();
			frame_time_ms_ = timer.GetElapsedInMilliseconds();
			timer.Reset();

			accumulator_ += frame_time_ms_;

			window_->OnUpdate();
			
			while (accumulator_ >= MS_PER_UPDATE) {
				for (auto& layer : layers_) {
					layer->OnUpdate();
				}

				accumulator_ -= MS_PER_UPDATE;
			}

			Renderer2D::BeginBatch();
			for (auto& layer : layers_) {
				layer->OnRender(accumulator_ / MS_PER_UPDATE);
			}
			Renderer2D::EndBatch();

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
		Renderer2D::SetProjection(glm::ortho(0.0f, (float)event.width_, (float)event.height_, 0.0f));
	}
	void Application::PushLayer(Layer* layer)
	{
		layers_.emplace_back(std::move(layer));
	}
	void Application::SetVsync(bool vsync)
	{
		if (vsync && !Get().IsVsync()) {
			glfwSwapInterval(1);
			Get().vsync_ = true;
		}
		else if (!vsync && Get().IsVsync()){
			glfwSwapInterval(0);
			Get().vsync_ = false;
		}
	}
	double Application::GetFrameTime()
	{
		return frame_time_ms_;
	}
	Vec2 Application::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(Get().window_->GetWindowHandle(), &x, &y);
		return Vec2(x, y);
	}
}	
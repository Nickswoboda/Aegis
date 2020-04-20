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
	float Application::time_step_ = 1.0f / 60.0f;
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
		Timer timer;
		timer.Start();
		double accumulator_ = 0.0;
		while (running_) {

			timer.Update();
			frame_time_ms_ = timer.GetElapsedInSeconds();
			timer.Reset();

			accumulator_ += frame_time_ms_;

			window_->OnUpdate();
			
			while (accumulator_ >= time_step_) {
				for (auto& layer : layers_) {
					layer->OnUpdate();
				}

				accumulator_ -= time_step_;
			}

			for (auto& layer : layers_) {
				layer->OnRender(accumulator_ / time_step_);
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
	float Application::GetTimeStep()
	{
		return time_step_;
	}
	void Application::SetTimeStep(float time_step)
	{
		time_step_ = time_step;
	}
	double Application::GetFrameTime()
	{
		return frame_time_ms_ * 1000;
	}
	Vec2 Application::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(Get().window_->GetWindowHandle(), &x, &y);
		return Vec2(x, y);
	}
}	
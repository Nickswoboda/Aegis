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

	double Application::frame_time_sec_ = 0.0;
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

		scene_mgr_.PushScene(std::unique_ptr<Scene>(new BaseScene()));


		Renderer2D::Init(width, height);
		default_font_ = std::make_shared<Font>("assets/fonts/WorkSans-Regular.ttf", 16);
		Renderer2D::SetFont(default_font_);
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
			frame_time_sec_ = timer.GetElapsedInSeconds();
			timer.Reset();

			accumulator_ += frame_time_sec_;

			window_->OnUpdate();
			
			while (accumulator_ >= time_step_) {
				scene_mgr_.CurrentScene()->Update();

				accumulator_ -= time_step_;
			}

			scene_mgr_.CurrentScene()->Render(accumulator_ / time_step_);

			if (show_frame_time_) {
				Renderer2D::SetFont(default_font_);
				DrawText(std::to_string(frame_time_sec_ * 1000), { 0, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f });
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
			scene_mgr_.CurrentScene()->OnEvent(event);
		}
	}

	void Application::OnWindowClose()
	{
		running_ = false;
	}
	void Application::OnWindowResize(const WindowResizeEvent& event)
	{
		glViewport(0, 0, event.width_, event.height_);
		scene_mgr_.CurrentScene()->camera_.SetProjection(0.0f, (float)event.width_, (float)event.height_, 0.0f);
		window_->width_ = event.width_;
		window_->height_ = event.height_;
	}

	void Application::PushScene(std::unique_ptr<Scene> scene)
	{
		scene_mgr_.PushScene(std::move(scene));
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
		return frame_time_sec_ * 1000;
	}
	Vec2 Application::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(Get().window_->GetWindowHandle(), &x, &y);
		return Vec2(x, y);
	}
}	
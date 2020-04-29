#include "Application.h"

#include "Renderer/Renderer.h"
#include "Font.h"
#include "Timer.h"
#include "Assert.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <chrono>

namespace Aegis {

	std::unique_ptr<Window> Application::window_;
	std::shared_ptr<Font> Application::default_font_;
	SceneManager Application::scene_mgr_;
	double Application::frame_time_sec_ = 0.0;
	float Application::time_step_ = 1.0f / 60.0f;
	bool Application::running_ = true;
	bool Application::show_frame_time_ = false;

	Application::Application(int width, int height)
	{
		if (!glfwInit()) {
			std::cout << "Unable to initiate GLFW.\n";
			return;
		}

		window_ = std::make_unique<Window>("Aegis", width, height);
		window_->SetEventCallbacks(std::bind(&Application::OnEvent, std::placeholders::_1));

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
		window_->OnResize(event);
	}

	void Application::PushScene(std::unique_ptr<Scene> scene)
	{
		scene_mgr_.PushScene(std::move(scene));
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
}	
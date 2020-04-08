#pragma once

#include "Window.h"
#include "Event.h"
#include "Font.h"
#include "Layer.h"
#include "Math.h"

#include <memory>
#include <vector>

namespace Aegis {

	class Application
	{
	public:
		Application(int width, int height);
		~Application();

		void Run();
		void OnEvent(Event& event);
		void OnWindowClose();
		void OnWindowResize(const WindowResizeEvent& event);
		void PushLayer(Layer* layer);
		static double GetFrameTime();
		static Application& Get() { return *instance_; }
		static Vec2 GetMousePos();
		static int GetWindowHeight() { return Get().window_->height_; }
		static int GetWindowWidth() { return Get().window_->width_; }
		static bool IsVsync() { return  Get().vsync_; }
		static void SetVsync(bool vsync);
	private:
		std::unique_ptr<Window> window_;
		static Application* instance_;
		std::vector<std::unique_ptr<Layer>> layers_;
		static double frame_time_ms_;
		bool running_ = true;
		bool vsync_ = false;
	};
}
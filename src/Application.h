#pragma once

#include "Window.h"
#include "Event.h"
#include "Font.h"
#include "Layer.h"

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
		void PushLayer(Layer* layer);
		static void SetVsync(bool vsync);
		static double GetFrameTime();
	private:
		std::unique_ptr<Window> window_;
		bool running_ = true;
		std::vector<std::unique_ptr<Layer>> layers_;
		static double frame_time_ms_;
	};
}
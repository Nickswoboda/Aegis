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
	private:
		std::unique_ptr<Window> window_;
		std::unique_ptr<Font> font_;
		bool running_ = true;
		std::vector<std::unique_ptr<Layer>> layers_;
	};
}
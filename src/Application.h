#pragma once

#include "Window.h"
#include "Event.h"
#include "Renderer.h"

#include <memory>

namespace Aegis {

	class Application
	{
	public:
		Application(int width, int height);
		~Application();

		void Run();
		void OnEvent(Event& event);
		void OnWindowClose();
	private:
		std::unique_ptr<Window> window_;
		std::unique_ptr<VertexArray> vertex_array_;
		bool running_ = true;
	};
}
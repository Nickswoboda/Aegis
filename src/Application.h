#pragma once

#include "Window.h"
#include "Event.h"
#include "Font.h"
#include "Layer.h"
#include "Scene.h"

#include <memory>
#include <vector>


namespace Aegis {

	class Application
	{
	public:

		static void Shutdown();

		static void CreateWindow(const std::string& title, int width, int height); //add flags for resizable/moveable/decorated/etc

		static void Run();
		static void Quit() { running_ = false; }

		static void OnEvent(Event& event);
		static void OnWindowClose();
		static void OnWindowResize(const WindowResizeEvent& event);

		static Window& GetWindow() { return *window_; }

		static void PushScene(std::unique_ptr<Scene> scene);

		static float GetTimeStep();
		static void SetTimeStep(float time_step);

		static double GetFrameTime();
		static void ShowFrameTime(bool show) {show_frame_time_ = show; }

	private:
		static std::unique_ptr<Window> window_;
		static std::shared_ptr<Font> default_font_;
		static SceneManager scene_mgr_;

		static double frame_time_sec_;
		static float time_step_;

		static bool show_frame_time_;
		static bool running_;
	};
}
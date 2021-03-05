#pragma once

#include "Event.h"
#include "../Math/Vec2.h"
#include "../Math/AABB.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <functional>
namespace Aegis {

	enum WindowFlag
	{
		WindowFlag_None =			0,
		WindowFlag_Centered =		1 << 0, //Centers window on monitor on creation
		WindowFlag_NonResizable =	1 << 1, //Disallow user from resizing monitor
		WindowFlag_Undecorated =	1 << 2  //Do not show borders/close/maximize/minimize/etc
	};

	enum class ScreenMode
	{
		Fullscreen,
		Windowed,
		FullscreenWindow
	};

	class Window
	{
	public:
		Window(const std::string& title, int width, int height, int flags);
		~Window();

		GLFWwindow* GetWindowHandle() { return window_handle_; };

		void SetEventCallbacks(std::function<void(Event&)> callback);
		void OnResize(const WindowResizeEvent& event);

		void OnUpdate();

		void CenterOnScreen();

		AABB GetViewport() const;

		void SetPos(int x, int y);
		Vec2 GetPos();

		void SetSize(int x, int y);
		Vec2 GetSize();

		bool IsVsync() { return vsync_; }
		void SetVsync(bool vsync);

		void SetScreenMode(ScreenMode screen_mode);
		inline ScreenMode GetScreenMode() { return screen_mode_; }
		void SetResolution(int x, int y);
		Vec2 GetResolution() { return resolution_; }

		void SetResizable(bool resizable);
		bool IsResizable();

		void SetDecorated(bool decorated);
		bool IsDecorated();
		
		Vec2 GetMousePos();
		bool IsMousePressed();

	private:
		//ratio between resolution and window size. Useful for buttons that change size due to resolution changes
		Vec2 pos_;
		Vec2 size_;
		//size in windowed mode, does not update when fullscreen
		Vec2 windowed_size_;
		Vec2 mouse_pos_scale_ = { 1,1 };
		Vec2 resolution_;
		std::function<void(Event&)> callback_;
		GLFWwindow* window_handle_;
		ScreenMode screen_mode_ = ScreenMode::Windowed;
		bool vsync_ = false;
	};
}

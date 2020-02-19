#pragma once

namespace Aegis {

	enum class EventType {
		WindowResized,
		WindowClosed,
		KeyPressed,
		MouseMoved,
		MouseClicked,
		MouseScrolled
	};

	class Event
	{
	public:
		bool handled_ = false;

		virtual EventType GetEventType() = 0;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:width_(width), height_(height)
		{}

		unsigned int width_, height_;

		virtual EventType GetEventType() override { return EventType::WindowResized; };

	};

	class WindowCloseEvent : public Event
	{
	public:
		virtual EventType GetEventType() override { return EventType::WindowClosed; };
	};

	class KeyEvent: public Event
	{
	public:
		KeyEvent(int key, int scancode, int action, int mods)
			:key_(key), scancode_(scancode), action_(action), mods_(mods)
		{}

		virtual EventType GetEventType() override { return EventType::KeyPressed; };

		int key_, scancode_, action_, mods_;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(double x_pos, double y_pos)
			:x_pos_(x_pos), y_pos_(y_pos)
		{}

		virtual EventType GetEventType() override { return EventType::MouseMoved; };

		double x_pos_, y_pos_;
	};
	class MouseClickEvent : public Event
	{
	public:
		MouseClickEvent(int button, int action, int mods)
			:button_(button), action_(action), mods_(mods)
		{}

		virtual EventType GetEventType() override { return EventType::MouseClicked; };

		int button_, action_, mods_;
	};
	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(double x_offset, double y_offset)
			:x_offset_(x_offset), y_offset_(y_offset)
		{}

		virtual EventType GetEventType() override { return EventType::MouseScrolled; };

		double x_offset_, y_offset_;
	};
}
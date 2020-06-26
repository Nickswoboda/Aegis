#pragma once
#include "Widget.h"
#include "../Event.h"
#include "../Math/AABB.h"
#include "../Math/Vec4.h"
#include "../Font.h"

#include "array"
#include <functional>

namespace Aegis {
	class Button : public Widget
	{
	public:
		enum State
		{
			Normal,
			Pressed,
			Hovered,
			NumStates
		};
		Button(const std::string& text, std::function<void()> callback);
		Button(AABB rect, const std::string& text, std::function<void()> callback);

		bool IsPressed(int action);
		void OnEvent(Event& event) override;
		void Render(float delta_time = 0.0f) override;

		void SetStateTexture(State state, std::shared_ptr<Texture> texture);
		std::array<std::shared_ptr<Texture>, NumStates> textures_;
		std::string text_;
		bool hovered_ = false;
		std::function<void()> callback_;
		State state_ = State::Normal;
	};
}

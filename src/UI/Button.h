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
		Button(AABB rect, const std::string& label);

		bool IsPressed(int action);
		void OnEvent(Event& event) override;
		void Render() override;

		void SetStateTexture(State state, std::shared_ptr<Texture> texture);
		std::array<std::shared_ptr<Texture>, NumStates> textures_;
		std::string text_;
		bool hovered_ = false;
		State state_ = State::Normal;
	};
}

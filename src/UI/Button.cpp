#include "Button.h"

#include "../Core/MouseCodes.h"
#include "../Core/Application.h"
#include "../Renderer/Renderer.h"

namespace Aegis {
	Button::Button(AABB rect, const std::string& label)
		: Widget(rect), text_(label)
	{
		AddSignal("pressed");
		AddSignal("double pressed");
		AddSignal("entered");
		AddSignal("exited");
	}

	bool Button::IsPressed(int action)
	{
		//button must be pressed and released while hovering in ordering for it to be considered to be pressed
		if (action == AE_BUTTON_PRESS && state_ == State::Hovered) {
			state_ = State::Pressed;
		}
		else if (action == AE_BUTTON_RELEASE && hovered_ && state_ == State::Pressed) {
			state_ = State::Hovered;
			return true;
		}
		else {
			state_ = State::Normal;
		}
		return false;
	}

	void Button::Render() const
	{
		if (visible_){
			if (textures_[state_]){
				DrawQuad(rect_.pos, rect_.size, *textures_[state_], { 1.0f, 1.0f, 1.0f, 1.0f }, z_idx_);
			}
			else{
				DrawQuad(rect_.pos, rect_.size, {0.2f, 0.2f, 0.8f, 1.0f}, z_idx_);
			}
			if (!text_.empty()){
				if (font_){
					Renderer2D::SetFont(font_);
				}
				DrawText(text_, rect_.pos, { 1.0, 1.0f, 1.0f, 1.0f }, z_idx_);
			}
		}
	}

	void Button::OnEvent(Event& event)
	{
		auto mouse_movement = dynamic_cast<MouseMoveEvent*>(&event);
		if (mouse_movement){
			//have to use Window GetMousePos because it takes resolution into account unlike the mouse_pos
			//maybe take mouse_move event take into account resolution?
			if (PointInAABB(Application::GetWindow().GetMousePos(), rect_)) {
				if (state_ == State::Normal) {
					Emit("entered");
				}
				hovered_ = true;
				if (state_ != State::Pressed){
					state_ = State::Hovered;
				}
			}
			else{
				if (state_ != State::Normal) {
					Emit("exited");
				}
				hovered_ = false;
				if (state_ == State::Hovered){
					state_ = State::Normal;
				}
			}
				
			return;
		}
		auto click = dynamic_cast<MouseClickEvent*>(&event);
		if (click) {
			if (click->action_ == AE_MOUSE_DOUBLE_PRESS && PointInAABB(Application::GetWindow().GetMousePos(), rect_)){
				Emit("double pressed");
				event.handled_ = true;
			}
			else if (IsPressed(click->action_)) {
				Emit("pressed");
				event.handled_ = true;
			}
		}
	}

	void Button::SetStateTexture(State state, std::shared_ptr<Texture> texture)
	{
		textures_[state] = texture;

		if (state_ == State::Normal){
			if (textures_[State::Hovered] == nullptr){
				textures_[State::Hovered] = texture;
			}
			if (textures_[State::Pressed] == nullptr){
				textures_[State::Pressed] = texture;
			}
		}
	}
}

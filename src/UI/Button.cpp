#include "Button.h"

#include "../MouseCodes.h"
#include "../Application.h"
#include "../Renderer/Renderer.h"

namespace Aegis {
	Button::Button(const std::string& text, std::function<void()> callback)
		: Widget(), text_(text), callback_(callback)
	{
	}
	Button::Button(AABB rect, const std::string& text, std::function<void()> callback)
		: Widget(rect), text_(text), callback_(callback)
	{
	}
	
	bool Button::IsPressed(int action)
	{
		//button must be pressed and released while hovering in ordering for it to be considered to be pressed
		if (action == AE_BUTTON_PRESS) {
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

	void Button::Render(float delta_time)
	{
		if (textures_[state_]){
			DrawQuad(rect_.pos, rect_.size, textures_[state_]);
		}

		if (!text_.empty()){
			Renderer2D::SetFont(font_);
			DrawText(text_, rect_.pos, { 1.0, 1.0f, 1.0f, 1.0f });
		}
	}

	void Button::OnEvent(Event& event)
	{
		auto mouse_movement = dynamic_cast<MouseMoveEvent*>(&event);
		if (mouse_movement){
			if (PointInAABB(Vec2(mouse_movement->x_pos_, mouse_movement->y_pos_), rect_)) {
				hovered_ = true;
				if (state_ != State::Pressed){
					state_ = State::Hovered;
				}
			}
			else{
				hovered_ = false;
				if (state_ == State::Hovered){
					state_ = State::Normal;
				}
			}
				
			return;
		}
		auto click = dynamic_cast<MouseClickEvent*>(&event);
		if (click) {
			if (IsPressed(click->action_)) {
				callback_();
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

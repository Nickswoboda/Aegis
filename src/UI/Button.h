#pragma once
#include "Widget.h"
#include "../Core/Event.h"
#include "../Math/AABB.h"
#include "../Math/Vec4.h"
#include "../Renderer/Font.h"

#include <array>
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
		Button(AABB rect, const std::string& label = "");

		bool IsPressed(int action);
		void OnEvent(Event& event) override;
		void Render() const override;

		const std::string& GetText() const;
		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font) override;

		void SetStateTexture(State state, std::shared_ptr<Texture> texture);
		void SetStateBgColor(State state, const Vec4& color);

		int border_size_ = 0;
		Vec4 border_color_ = {0.0f, 0.0f, 0.0f, 1.0f};
		State state_ = State::Normal;
	private:
		void UpdateTextRenderPos();
		std::string text_;
		Vec2 text_pos_;
		bool hovered_ = false;
		std::array<Vec4, NumStates> bg_colors_;
		std::array<std::shared_ptr<Texture>, NumStates> textures_;
	};
}

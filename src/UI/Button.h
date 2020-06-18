#pragma once
#include "UIWidget.h"
#include "../Event.h"
#include "../Math/AABB.h"
#include "../Math/Vec4.h"
#include "../Font.h"
#include <functional>

namespace Aegis {
	class Button : public UIWidget
	{
	public:

		Button(AABB rect, const std::string& text, std::shared_ptr<Font> font, std::function<void()> callback);

		bool IsPressed(int action);
		void OnEvent(Event& event) override;
		void Render(float delta_time = 0.0f) override;


		AABB rect_;
		Vec4 color_ = { 0.2, 0.4, 0.9, 1.0 };
		std::string text_;
		std::shared_ptr<Font> font_;
		bool pressed_ = false;
		std::function<void()> callback_;
	};
}

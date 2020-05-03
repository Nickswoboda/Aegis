#pragma once

#include "Math/AABB.h"
#include "Math/Vec4.h"
#include "Font.h"

namespace Aegis {
	class Button
	{
	public:
		Button(AABB rect);
		Button(AABB rect, std::string text, std::shared_ptr<Font> font);
		bool IsPressed(int action);
		void Render();


		AABB rect_;
		Vec4 color_ = { 0.2, 0.4, 0.9, 1.0 };
		std::string text_;
		std::shared_ptr<Aegis::Font> font_;
		bool pressed_ = false;
	};
}
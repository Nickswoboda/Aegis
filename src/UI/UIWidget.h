#pragma once

#include "../Event.h"
#include "../Font.h"
#include "../Math/AABB.h"

#include <memory>

namespace Aegis {

	class UIWidget
	{
	public:
		UIWidget(AABB rect = {0.0, 0.0, 0.0, 0.0})
			:rect_(rect) {}
		virtual ~UIWidget(){};
		virtual void OnEvent(Event& event) = 0;
		virtual void Render(float delta_time) = 0;

		void SetFont(std::shared_ptr<Font>& font) {font_ = font;}

		std::shared_ptr<Font> font_;
		AABB rect_;
	};
}

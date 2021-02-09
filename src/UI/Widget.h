#pragma once

#include "../Object.h"
#include "../Event.h"
#include "../Font.h"
#include "../Math/AABB.h"

#include <memory>

namespace Aegis {

	class Widget : public Object
	{
	public:
		Widget(AABB rect = { 0.0, 0.0, 0.0, 0.0 });
		virtual ~Widget() = default;
		virtual void OnEvent(Event& event) = 0;
		virtual void Render() = 0;

		virtual void SetFont(std::shared_ptr<Font> font) {font_ = font;}

		std::shared_ptr<Font> font_;
		AABB rect_;
		float z_idx_ = 0.0f;
		bool visible_ = true;
	};
}

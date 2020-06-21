#pragma once

#include "../Event.h"
#include "../Font.h"

#include <memory>

namespace Aegis {

	class UIWidget
	{
	public:
		virtual ~UIWidget(){};
		virtual void OnEvent(Event& event) = 0;
		virtual void Render(float delta_time) = 0;

		void SetFont(std::shared_ptr<Font>& font) {font_ = font;}
	protected:
		std::shared_ptr<Font> font_;
	};
}

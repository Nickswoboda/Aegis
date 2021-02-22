#pragma once

#include "../Core/Object.h"
#include "../Core/Event.h"
#include "../Renderer/Font.h"
#include "../Math/AABB.h"

#include <memory>

namespace Aegis {

	class Widget : public Object
	{
	public:
		Widget(AABB rect = { 0.0, 0.0, 0.0, 0.0 });
		virtual ~Widget() = default;
		virtual void OnEvent(Event& event) = 0;
		virtual void Render() const = 0;

		virtual void SetPos(Aegis::Vec2 pos); 
		virtual void SetSize(Aegis::Vec2 size);

		const AABB& GetRect() const;
		virtual void SetFont(std::shared_ptr<Font> font);

		std::shared_ptr<Font> font_;
		float z_idx_ = 0.0f;
		bool visible_ = true;
	protected:
		AABB rect_;
	};
}

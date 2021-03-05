#pragma once

#include "Widget.h"
#include "../Math/Vec4.h"

namespace Aegis{

	enum Alignment 
	{
		Top =		1 << 0,
		Bottom =	1 << 1,
		VCenter =   1 << 2,
		Left =      1 << 3,
		Right =     1 << 4,
		HCenter =   1 << 5,
		Center =	VCenter | HCenter
	};

	inline Alignment operator|(Alignment a, Alignment b)
	{
		return static_cast<Alignment>(static_cast<int>(a) | static_cast<int>(b));
	}

	class Container: public Widget
	{
	public:
		enum Orientation
		{
			Horizontal,
			Vertical
		};

		Container(AABB rect_, Orientation orientation, int padding, Alignment alignment = Alignment::Top | Alignment::Left);

		void Render() const override;
		void OnEvent(Event& event) override;
		void SetPos(Aegis::Vec2 pos) override;

		template<typename T, typename... Args>
		std::shared_ptr<T> AddWidget(Args&&... args)
		{
			auto ref = std::make_shared<T>(std::forward<Args>(args)...);
			AddWidget(ref);
			return ref;
		}

		void AddWidget(std::shared_ptr<Widget> widget);
		void UpdateWidgets();

		void SetAlignment(Alignment alignment);

		Vec4 bg_color_ = {0.0f, 0.0f, 1.0f, 0.0f};
		int padding_;

	private:
		bool WidgetFits(const Widget& widget) const;
		void AlignWidget(Widget& widget, Vec2& pen_pos);

		float occupied_space_;
		Orientation orientation_;
		Alignment alignment_ = Alignment::Top | Alignment::Left;
		std::vector<std::shared_ptr<Widget>> widgets_;
	};
}


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

		Container();

		void Render() const override;
		void OnEvent(Event& event) override;

		void SetPos(Vec2 pos) override;
		void SetSize(Vec2 size) override;

		template<typename T, typename... Args>
		std::shared_ptr<T> AddWidget(Args&&... args)
		{
			auto ref = std::make_shared<T>(std::forward<Args>(args)...);
			AddWidget(ref);
			return ref;
		}

		void AddWidget(std::shared_ptr<Widget> widget);

		void SetAlignment(Alignment alignment);

		void SetPadding(int padding);
		int GetPadding() const;

		void SetBgColor(const Vec4& bg_color);
		Vec4 GetBgColor() const;

	protected:
		virtual bool WidgetFits(const Widget& widget) const = 0;
		virtual void AlignWidget(Widget& widget, Vec2 pen_pos) = 0;
		virtual void UpdateWidgets() = 0;

		Vec4 bg_color_ = {0.0f, 0.0f, 1.0f, 0.0f};
		int padding_ = 2;
		float occupied_space_;
		Alignment alignment_ = Alignment::Top | Alignment::Left;
		std::vector<std::shared_ptr<Widget>> widgets_;
	};

	class HContainer : public Container
	{
		bool WidgetFits(const Widget& widget) const override;
		void AlignWidget(Widget& widget, Vec2 pen_pos) override;
		void UpdateWidgets() override;
	};

	class VContainer : public Container
	{
		bool WidgetFits(const Widget& widget) const override;
		void AlignWidget(Widget& widget, Vec2 pen_pos) override;
		void UpdateWidgets() override;
	};
}


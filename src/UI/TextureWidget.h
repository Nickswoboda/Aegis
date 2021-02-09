#pragma once

#include "Widget.h"

namespace Aegis{

	class TextureWidgetBase : public Widget
	{
	public:
		TextureWidgetBase(Vec2 pos, Vec2 size, Vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
		void OnEvent(Event& event) override {};
		Vec4 color_;
		Vec2 pos_;
		Vec2 size_;
	};

	class TextureWidget : public TextureWidgetBase
	{
	public:

		TextureWidget(std::shared_ptr<Texture> texture, const Vec2 pos, const Vec4& color = {1.0f, 1.0f, 1.0f, 1.0f});
		TextureWidget(const Vec4& color, const Vec2 pos, const Vec2 size);

		void Render() override;

		std::shared_ptr<Texture> texture_;
	};

	class SubTextureWidget : public TextureWidgetBase
	{
	public:
		SubTextureWidget(std::shared_ptr<SubTexture> subtexture, const Vec2 pos, const Vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		void Render() override;

		std::shared_ptr<SubTexture> subtexture_;
	};
}

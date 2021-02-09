#include "TextureWidget.h"

#include "../Renderer/Renderer.h"

namespace Aegis {
	TextureWidgetBase::TextureWidgetBase(Vec2 pos, Vec2 size, Vec4 color)
		:color_(color), pos_(pos), size_(size) {}
	TextureWidget::TextureWidget(std::shared_ptr<Texture> texture, const Vec2 pos, const Vec4& color)
		: TextureWidgetBase(pos, texture->size_, color), texture_(texture) {};

	TextureWidget::TextureWidget(const Vec4& color, const Vec2 pos, const Vec2 size)
		: TextureWidgetBase(pos, size, color) {};

	void TextureWidget::Render()
	{
		if (visible_) {
			if (texture_) {
				DrawQuad(pos_, size_, *texture_);
			}
			else {
				DrawQuad(pos_, size_, color_);
			}
		}
	}

	SubTextureWidget::SubTextureWidget(std::shared_ptr<SubTexture> subtexture, const Vec2 pos, const Vec4& color)
		: TextureWidgetBase(pos, subtexture->size_, color), subtexture_(subtexture) {};

	void SubTextureWidget::Render()
	{
		if (visible_) {
			DrawQuad(pos_, *subtexture_);
		}
	}
}

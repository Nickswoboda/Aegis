#include "TextureWidget.h"

#include "../Renderer/Renderer.h"

namespace Aegis{
	TextureWidget::TextureWidget(std::shared_ptr<Texture> texture, const Vec2 pos, const Vec2 size, const Vec4& color)
		: texture_(texture), color_(color), pos_(pos), size_(size) {};
	
	TextureWidget::TextureWidget(const Vec4& color, const Vec2 pos, const Vec2 size)
		: color_(color), pos_(pos), size_(size) {};

	void TextureWidget::Render()
	{
		if (visible_){
			if (texture_){
				DrawQuad(pos_, size_, texture_);
			}
			else{
				DrawQuad(pos_, size_, color_);
			}
		}
	}
}

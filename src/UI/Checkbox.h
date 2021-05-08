#pragma once 

#include "Widget.h"
#include "Button.h"
#include "Container.h"
#include "Label.h"

#include <string>

namespace Aegis{

	class Checkbox : public Widget
	{
	public:
		Checkbox(const std::string& label);

		void OnEvent(Event& event) override;
		void Render() const override;

		void SetFont(std::shared_ptr<Font> font) override;
		void SetPos(Vec2 pos) override;
		void SetSize(Vec2 size) override;

		void SetText(const std::string& text);
		void SetState(bool checked);
		void SetStateTexture(bool checked, std::shared_ptr<Texture> texture);
		void SetStateColor(bool checked, const Vec4& color);

		bool checked_ = false;

	private:
		void UpdateHBoxSize();
		void UpdateButtonTexture();

		HContainer h_box_;
		std::shared_ptr<Button> button_;
		std::shared_ptr<Label> label_;

		std::array<std::shared_ptr<Texture>, 2> textures_;
		std::array<Vec4, 2> colors_;
	};
}

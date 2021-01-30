#pragma once 

#include "Widget.h"
#include "Button.h"

#include <string>

namespace Aegis{

	class Checkbox : public Widget
	{
	public:
		Checkbox(const std::string& label, AABB box);
		void OnEvent(Event& event) override;
		void Render() override;
		void SetFont(std::shared_ptr<Font> font) override;

		void SetTexture(bool checked, std::shared_ptr<Texture> texture);

		std::string label_;
		std::unique_ptr<Button> button_;
		bool checked_ = false;
		int label_offset_ = 0;
		std::array<std::shared_ptr<Texture>, 2> textures_;
	};
}

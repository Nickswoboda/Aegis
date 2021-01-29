#pragma once 

#include "Widget.h"
#include "Button.h"

#include <string>

namespace Aegis{

	class Checkbox : public Widget
	{
	public:
		Checkbox(const std::string& label, AABB box, std::function<void(bool)> callback);
		~Checkbox();
		void OnEvent(Event& event) override;
		void Render(float delta_time) override;
		void SetFont(std::shared_ptr<Font>& font) override;

		void SetTexture(bool checked, std::shared_ptr<Texture> texture);

		std::string label_;
		Button* button_;
		bool checked_ = false;
		std::function<void(bool)> callback_;
		int label_offset_ = 0;
		std::array<std::shared_ptr<Texture>, 2> textures_;
	};
}

#include "FontManager.h"

namespace Aegis{
	std::unordered_map<std::string, std::shared_ptr<Font>> FontManager::fonts_;
	std::shared_ptr<Font> FontManager::Load(const std::string& path, int size)
	{
		std::string index = path + std::to_string(size);
		if (fonts_.find(index) != fonts_.end()) {
			return fonts_[index];
		}

		std::shared_ptr<Font> font = std::make_shared<Font>(path, size);
		fonts_.emplace(index, font);

		return font;
	}

}

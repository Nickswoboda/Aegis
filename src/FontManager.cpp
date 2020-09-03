#include "FontManager.h"

namespace Aegis{
	std::unordered_map<std::string, std::shared_ptr<Font>> FontManager::fonts_;
	std::shared_ptr<Font> FontManager::Load(const std::string& path, int size)
	{
		if (fonts_.find(path) != fonts_.end()) {
			return fonts_[path];
		}

		std::shared_ptr<Font> font = std::make_shared<Font>(path, size);
		fonts_.emplace(path + std::to_string(size), font);

		return font;
	}

}

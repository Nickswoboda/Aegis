#pragma once

#include "Font.h"

#include <memory>
#include <unordered_map>

namespace Aegis {
	class FontManager
	{
	public:

		FontManager(FontManager const&) = delete;
		FontManager& operator=(FontManager const&) = delete;

		static FontManager& Instance()
		{
			static FontManager* instance = new FontManager();
			return *instance;
		}

		std::shared_ptr<Font> Load(const std::string& path, int size)
		{
			if (fonts_.find(path) != fonts_.end()) {
				return fonts_[path];
			}

			std::shared_ptr<Font> font = std::make_shared<Font>(path, size);
			fonts_.emplace(path + std::to_string(size), font);

			return font;
		}
	private:
		FontManager() {};
		std::unordered_map<std::string, std::shared_ptr<Font>> fonts_;
	};
}
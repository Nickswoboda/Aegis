#pragma once

#include "Font.h"

#include <memory>
#include <unordered_map>

namespace Aegis {
	class FontManager
	{
	public:
		static std::shared_ptr<Font> Load(const std::string& path, int size);
	private:
		static std::unordered_map<std::string, std::shared_ptr<Font>> fonts_;
	};
}

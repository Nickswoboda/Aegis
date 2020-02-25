#pragma once

#include "Renderer/Texture.h"

#include <memory>
namespace Aegis {
	class Font {
	public:
		Font(const std::string& path, int size);

		std::unique_ptr<Texture> texture_;
	};
}
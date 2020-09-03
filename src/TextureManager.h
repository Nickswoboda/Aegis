#pragma once

#include "Renderer/Texture.h"

#include <unordered_map>
#include <memory>
namespace Aegis {
	class TextureManager
	{
	public:
		static std::shared_ptr<Texture> Load(const std::string& path);
	private:
		static std::unordered_map <std::string, std::shared_ptr<Texture>> textures_;
	};
}

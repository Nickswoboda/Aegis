#include "TextureManager.h"

namespace Aegis{
	std::unordered_map<std::string, std::shared_ptr<Texture>> TextureManager::textures_;

	std::shared_ptr<Texture> TextureManager::Load(const std::string& path)
	{
		if (textures_.find(path) != textures_.end()) {
			return textures_[path];
		}

		std::shared_ptr<Texture> texture = Texture::Create(path);
		textures_.emplace(path, texture);

		return texture;
	}
}

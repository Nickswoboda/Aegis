#pragma once

#include "Renderer/Texture.h"

#include <unordered_map>
#include <memory>
namespace Aegis {
	class TextureManager
	{
	public:

		TextureManager(TextureManager const&) = delete;
		TextureManager& operator=(TextureManager const&) = delete;

		static TextureManager& Instance() 
		{
			static TextureManager* instance = new TextureManager();
			return *instance;
		}
	

		std::shared_ptr<Texture> Load(const std::string& path)
		{
			if (textures_.find(path) != textures_.end()) {
				return textures_[path];
			}

			std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);
			textures_.emplace(path, texture);

			return texture;
		}

	private:
		TextureManager() {};
		std::unordered_map <std::string, std::shared_ptr<Texture>> textures_;
	};
}
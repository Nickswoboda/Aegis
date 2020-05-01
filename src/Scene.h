#pragma once

#include "Event.h"
#include "Renderer/Renderer.h"
#include "Camera.h"

#include <vector>
#include <memory>

namespace Aegis {

	class SceneManager;
	class Scene 
	{
	public:
		Scene();
		virtual void Update() = 0;
		virtual void Render(float delta_time) = 0;
		virtual void OnEvent(Event& event) = 0;

		SceneManager* manager_ = nullptr;
		Camera camera_;
	};

	class BaseScene : public Scene
	{
	public:
		BaseScene() {}

		virtual void Update() override {}
		virtual void Render(float delta_time) override { Aegis::RendererClear(); }
		virtual void OnEvent(Event& event) override {}
		
	};
	class SceneManager
	{
	public:
		SceneManager() {}
		void PushScene(std::unique_ptr<Scene> scene) { scene->manager_ = this; scenes_.push_back(std::move(scene)); }
		void PopScene() { if (scenes_.size() > 1) scenes_.pop_back();}
		void ReplaceScene(std::unique_ptr<Scene> scene) { scenes_.pop_back(); PushScene(std::move(scene));}
		std::unique_ptr<Scene>& CurrentScene() { return scenes_.back(); }

		void UpdateAllCameraProjections(float left, float right, float bottom, float top) { for (auto& scene : scenes_) { scene->camera_.SetProjection(left, right, bottom, top); }; }
	private:
		std::vector<std::unique_ptr<Scene>> scenes_;
	};
}
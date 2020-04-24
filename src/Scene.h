#pragma once

#include "Event.h"
#include "Renderer/Renderer.h"
#include "Camera.h"

#include <stack>
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
		void PushScene(std::unique_ptr<Scene> scene) { scene->manager_ = this; scenes_.push(std::move(scene)); }
		void PopScene() { if (scenes_.size() > 1) scenes_.pop();}
		void ReplaceScene(std::unique_ptr<Scene> scene) { scenes_.pop(); PushScene(std::move(scene));}
		std::unique_ptr<Scene>& CurrentScene() { return scenes_.top(); }
	private:
		std::stack<std::unique_ptr<Scene>> scenes_;
	};
}
#pragma once

#include "Event.h"

#include <stack>
#include <memory>

#include <iostream>
namespace Aegis {

	class SceneManager;
	class Scene 
	{
	public:
		Scene() {}
		virtual void Update() = 0;
		virtual void Render(float delta_time) = 0;
		virtual void OnEvent(Event& event) = 0;

		SceneManager* manager_ = nullptr;
	};

	class SceneManager
	{
	public:
		void PushScene(std::unique_ptr<Scene> scene) { scene->manager_ = this; scenes_.push(std::move(scene)); }
		void PopScene() { if (scenes_.size() > 1) scenes_.pop();}
		void ReplaceScene(std::unique_ptr<Scene> scene) { scenes_.pop(); PushScene(std::move(scene));}
		std::unique_ptr<Scene>& CurrentScene() { return scenes_.top(); }
	private:
		std::stack<std::unique_ptr<Scene>> scenes_;
	};

}
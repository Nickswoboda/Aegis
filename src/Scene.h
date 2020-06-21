#pragma once

#include "Event.h"
#include "Renderer/Renderer.h"
#include "Camera.h"
#include "UI/UILayer.h"

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
		UILayer* ui_layer_ = nullptr;
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
		void PushScene(std::unique_ptr<Scene> scene); 
		void PopScene();
		void ReplaceScene(std::unique_ptr<Scene> scene);
		std::unique_ptr<Scene>& CurrentScene();

		void UpdateAllCameraProjections(float left, float right, float bottom, float top);
	private:
		std::vector<std::unique_ptr<Scene>> scenes_;
	};
}

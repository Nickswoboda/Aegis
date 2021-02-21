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
		virtual ~Scene() = default;
		virtual void Update() = 0;
		virtual void Render(float delta_time) = 0;
		virtual void OnEvent(Event& event) = 0;

		SceneManager* manager_;
		std::unique_ptr<UILayer> ui_layer_;
		Camera camera_;
	};

	class BaseScene : public Scene
	{
	public:
		virtual void Update() override {}
		virtual void Render(float delta_time) override { Aegis::RendererClear(); }
		virtual void OnEvent(Event& event) override {}
		
	};
	class SceneManager
	{
	public:
		void Update();
		void Render(float dt);
		void OnEvent(Event& event);

		void PushScene(std::unique_ptr<Scene> scene); 
		void PopScene();
		void ReplaceScene(std::unique_ptr<Scene> scene);

		void UpdateAllCameraProjections(float left, float right, float bottom, float top);
	private:
		std::vector<std::unique_ptr<Scene>> scenes_;
	};
}

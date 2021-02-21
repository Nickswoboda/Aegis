#include "Scene.h"

#include "Application.h"
namespace Aegis{
	Scene::Scene()
		: camera_(0, Application::GetWindow().GetResolution().x, Application::GetWindow().GetResolution().y, 0)
	{

	}

	void SceneManager::Update()
	{
		scenes_.back()->Update();
	}

	void SceneManager::Render(float dt)
	{
		scenes_.back()->Render(dt);
		if (scenes_.back()->ui_layer_){
			scenes_.back()->ui_layer_->Render(dt);
		}
	}

	void SceneManager::OnEvent(Event& event)
	{
		scenes_.back()->OnEvent(event);
		if (scenes_.back()->ui_layer_){
			scenes_.back()->ui_layer_->OnEvent(event);
		}
	}

	void SceneManager::PushScene(std::unique_ptr<Scene> scene)
	{
		scene->manager_ = this;
		scenes_.push_back(std::move(scene));
	}

	void SceneManager::PopScene()
	{
		if (scenes_.size() > 1){
			scenes_.pop_back();
		}
	}

	void SceneManager::ReplaceScene(std::unique_ptr<Scene> scene)
	{
		scenes_.pop_back();
		PushScene(std::move(scene));
	}

	void SceneManager::UpdateAllCameraProjections(float left, float right, float bottom, float top)
	{
		for (auto& scene : scenes_){
			scene->camera_.SetProjection(left, right, bottom, top);
		}
	}

}


#include "Scene.h"

#include "Application.h"
namespace Aegis{
	Scene::Scene()
		: camera_(0, Application::GetWindow().GetResolution().x, Application::GetWindow().GetResolution().y, 0)
	{

	}

	void SceneManager::PushScene(std::unique_ptr<Scene> scene)
	{
		scene->manager_ = std::unique_ptr<SceneManager>(this);
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

	std::unique_ptr<Scene>& SceneManager::CurrentScene()
	{
		return scenes_.back();
	}

	void SceneManager::UpdateAllCameraProjections(float left, float right, float bottom, float top)
	{
		for (auto& scene : scenes_){
			scene->camera_.SetProjection(left, right, bottom, top);
		}
	}

}


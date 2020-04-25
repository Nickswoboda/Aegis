#include "Scene.h"

#include "Application.h"

Aegis::Scene::Scene()
	: camera_(0,Application::default_camera_size_.x, Application::default_camera_size_.y,0)
{

}

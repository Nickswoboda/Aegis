#include "Scene.h"

#include "Application.h"

Aegis::Scene::Scene()
	: camera_(0, Application::GetResolution().x, Application::GetResolution().y, 0)
{

}

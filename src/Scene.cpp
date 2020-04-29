#include "Scene.h"

#include "Application.h"

Aegis::Scene::Scene()
	: camera_(0, Application::GetWindow().GetResolution().x, Application::GetWindow().GetResolution().y, 0)
{

}

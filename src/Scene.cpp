#include "Scene.h"

#include "Application.h"

Aegis::Scene::Scene()
	: camera_(0,Application::GetWindowWidth(), Application::GetWindowHeight(),0)
{

}

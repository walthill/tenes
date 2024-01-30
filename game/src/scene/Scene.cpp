#include "raylib.h"
#include "scene\Scene.h"

int Scene::s_framesCounter = 0;
int Scene::s_finishScreen = 0;

void Scene::Init()
{
#if DEBUG
	auto str = "SCENE::Initializing " + GetName();
	TraceLog(LOG_TRACE, str.c_str());
#endif
	s_finishScreen = 0;
	s_framesCounter = 0;
}

void Scene::Unload()
{
#if DEBUG
	auto str = "SCENE::Unloading " + GetName();
	TraceLog(LOG_TRACE, str.c_str());
#endif
}

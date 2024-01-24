#include "scene\Scene.h"

int Scene::s_framesCounter = 0;
int Scene::s_finishScreen = 0;

void Scene::Init()
{
	s_finishScreen = 0;
	s_framesCounter = 0;
}
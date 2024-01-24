#include "Scene_Options.h"
#include "SceneManager.h"

void Scene_Options::Init()
{
	Scene::Init();
}

void Scene_Options::Update()
{
	// TODO: Update OPTIONS screen variables here!
}

void Scene_Options::Draw()
{
	// TODO: Draw OPTIONS screen here!
}

void Scene_Options::Unload()
{
	// TODO: Unload OPTIONS screen variables here!
}

void Scene_Options::TryFinish()
{
	if (s_finishScreen)
	{
		SceneManager::TransitionToScreen(TITLE);
	}
}

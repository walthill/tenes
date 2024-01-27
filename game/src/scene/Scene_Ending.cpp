#include "Scene_Ending.h"
#include "SceneManager.h"

void Scene_Ending::Init()
{
	// TODO: Initialize ENDING screen variables here!
	Scene::Init();
}

void Scene_Ending::Update()
{
	// TODO: Update ENDING screen variables here!
}

void Scene_Ending::Draw()
{
	// TODO: Draw ENDING screen here!
}

void Scene_Ending::Unload()
{
	// TODO: Unload ENDING screen variables here!
	Scene::Unload();
}

void Scene_Ending::TryFinish()
{
	if (s_finishScreen == 1) 
		SceneManager::TransitionToScreen(TITLE);
}

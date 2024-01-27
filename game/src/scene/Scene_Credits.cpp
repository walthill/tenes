#include "Scene_Credits.h"
#include "SceneManager.h"

void Scene_Credits::Init()
{
	// TODO: Initialize CREDITS screen variables here!
	Scene::Init();
}

void Scene_Credits::Update()
{
	// TODO: Update CREDITS screen variables here!
}

void Scene_Credits::Draw()
{
	// TODO: Draw CREDITS screen here!
}

void Scene_Credits::Unload()
{
	// TODO: Unload CREDITS screen variables here!
	Scene::Unload();
}

void Scene_Credits::TryFinish()
{
	if (s_finishScreen == 1)
		SceneManager::TransitionToScreen(TITLE);
}

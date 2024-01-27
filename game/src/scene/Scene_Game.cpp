#include "Scene_Game.h"
#include "SceneManager.h"
#include "raylib.h"
#include "Game.h"

void Scene_Game::Init()
{
	Scene::Init();
}

void Scene_Game::Update()
{
	// TODO: Update GAMEPLAY screen variables here!

	GM->Update();
}

void Scene_Game::Draw()
{
	// TODO: Draw GAMEPLAY screen here!
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RAYWHITE);

	GM->Render();
}

void Scene_Game::Unload()
{
	// TODO: Unload GAMEPLAY screen variables here!
	Scene::Unload();
}

void Scene_Game::TryFinish()
{
	if (s_finishScreen == 1)
		SceneManager::TransitionToScreen(ENDING);
}

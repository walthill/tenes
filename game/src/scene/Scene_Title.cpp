#include "Scene_Title.h"
#include "raylib.h"
#include "SceneManager.h"

void Scene_Title::Init()
{
	Scene::Init();
}

void Scene_Title::Update()
{ 
    // TODO: Update TITLE screen variables here!

    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER))
    {
        //finishScreen = 1;   // OPTIONS
        s_finishScreen = 2;   // GAMEPLAY
    }
}

void Scene_Title::Draw()
{
    // TODO: Draw TITLE screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawText("TITLE SCREEN", 20, 10, 20, DARKGREEN);
    DrawText("Tense - PRESS ENTER TO PLAY", 120, 220, 20, WHITE);
}

void Scene_Title::Unload()
{
}

void Scene_Title::TryFinish()
{
    if (s_finishScreen == 1)
    {
        SceneManager::TransitionToScreen(OPTIONS);
    }
    else if (s_finishScreen == 2) 
    {
        SceneManager::TransitionToScreen(GAMEPLAY);
    }
}

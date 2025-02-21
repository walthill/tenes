#include "SceneManager.h"
#include "Scene_Logo.h"
#include "Scene_Title.h"
#include "Scene_Options.h"
#include "Scene_Game.h"
#include "Scene_Ending.h"
#include "Scene_Credits.h"
#include "Scene.h"
#include "raylib.h"

bool SceneManager::s_showFPS = false;
Scene* SceneManager::sp_currentScene = nullptr;
GameScreen SceneManager::s_currentScreenType = UNKNOWN;
bool SceneManager::s_onTransition = false;
bool SceneManager::s_transFadeOut = false;
GameScreen SceneManager::s_transFromScreen = UNKNOWN;
GameScreen SceneManager::s_transToScreen = UNKNOWN;
float SceneManager::s_transAlpha = 0.0f;

void SceneManager::SetScene(GameScreen a_screen)
{
    s_currentScreenType = a_screen;

    Scene* oldScene = nullptr;
    if (sp_currentScene != nullptr)
        oldScene = sp_currentScene;

    switch (s_currentScreenType)
    {
        case LOGO:      sp_currentScene = new Scene_Logo();     break;
        case TITLE:     sp_currentScene = new Scene_Title();    break;
        case GAMEPLAY:  sp_currentScene = new Scene_Game();     break;
        case OPTIONS:   sp_currentScene = new Scene_Options();  break;
        case ENDING:    sp_currentScene = new Scene_Ending();   break;
        case CREDITS:   sp_currentScene = new Scene_Credits();  break;
        default:        sp_currentScene = nullptr;              break;
    }

    if (sp_currentScene != nullptr)
        sp_currentScene->Init();

    if (oldScene != nullptr)
    {
        delete oldScene;
        oldScene = nullptr;
    }
}

void SceneManager::UpdateScene()
{
    if (!s_onTransition)
    {
        sp_currentScene->Update();
        sp_currentScene->TryFinish();
    }
    else 
    {
        UpdateTransition();    // Update transition (fade-in, fade-out)
    }
}

// Update transition effect(fade - in, fade - out)
void SceneManager::UpdateTransition()
{
    if (!s_transFadeOut)
    {
        s_transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (s_transAlpha > 1.01f)
        {
            s_transAlpha = 1.0f;

            // Unload current screen
            sp_currentScene->Unload();

            // Load next screen
            SceneManager::SetScene(s_transToScreen);

            // Activate fade out effect to next loaded screen
            s_transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        s_transAlpha -= 0.02f;

        if (s_transAlpha < -0.01f)
        {
            s_transAlpha = 0.0f;
            s_transFadeOut = false;
            s_onTransition = false;
            s_transFromScreen = UNKNOWN;
            s_transToScreen = UNKNOWN;
        }
    }
}

void SceneManager::DrawScene()
{
    // Draw
   //----------------------------------------------------------------------------------
    ClearBackground(BLACK);
    sp_currentScene->Draw();

    // Draw full screen rectangle in front of everything
    if (s_onTransition)
        DrawTransition();
#if DEBUG
    if(s_showFPS)
        DrawFPS(10, 10);
#endif
}

void SceneManager::Cleanup()
{
    if (sp_currentScene == nullptr)
        return;

    sp_currentScene->Unload();
    delete sp_currentScene;
    sp_currentScene = nullptr;
}

GameScreen SceneManager::GetCurrentSceneType()
{
    return s_currentScreenType;
}

// Request transition to next screen
void SceneManager::TransitionToScreen(GameScreen screen)
{
    s_onTransition = true;
    s_transFadeOut = false;
    s_transFromScreen = s_currentScreenType;
    s_transToScreen = screen;
    s_transAlpha = 0.0f;
}

// Draw transition effect (full-screen rectangle)
void SceneManager::DrawTransition()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, s_transAlpha));
}
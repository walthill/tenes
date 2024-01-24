#ifndef SCENE_H
#define SCENE_H

#include "Scene.h"

class SceneManager
{
	public:
		
		static void SetScene(GameScreen a_screen);
		static void UpdateScene();
		static void DrawScene();
		static void TransitionToScreen(GameScreen screen);
		static void Cleanup();

		static bool s_showFPS;
	
	private:
		static void DrawTransition();
		static void UpdateTransition();
		static Scene* sp_currentScene;
		static GameScreen s_currentScreenType;
		static bool s_onTransition;
		static bool s_transFadeOut;
		static GameScreen s_transFromScreen;
		static GameScreen s_transToScreen;
		static float s_transAlpha;
};

#endif // !SCENE_H

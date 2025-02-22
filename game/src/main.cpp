/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and run premake

*/

#include "raylib.h"
#include "Game.h"

const int windowX = 1000;
const int windowY = (int)(windowX / 1.5f);
const int tileSize = 64*2;

void InitGame()
{
	//set up game grid
	auto gameGrid = Grid(125, 150, 5, 3, tileSize);
	Game::LoadGame(windowX, windowY, tileSize, gameGrid);
}

void CleanupGame()
{
	Game::UnloadGame();
}

void Update()
{
	SceneManager::UpdateScene();
}

void Render()
{
	// drawing
	BeginDrawing();
	SceneManager::DrawScene();
	EndDrawing();
}

void InitRaylib()
{
	// set up the window
#if DEBUG
	SetTraceLogLevel(LOG_ALL);
#elif NDEBUG
	SetTraceLogLevel(LOG_INFO);
#endif
	SetTargetFPS(60);
	InitWindow(windowX, windowY, "Triple Creek");
	InitAudioDevice();
}

void CleanRaylib()
{
	// cleanup
	CloseAudioDevice();
	CloseWindow();
}

int main()
{
	InitRaylib();

#ifdef NDEBUG
	SceneManager::SetScene(LOGO);
#elif DEBUG 
	SceneManager::SetScene(TITLE);
#endif // !NDEBUG

	InitGame();

	// game loop
	while (!WindowShouldClose())
	{
		Update();
		Render();
	}

	CleanupGame();
	SceneManager::Cleanup();
	CleanRaylib();
	return 0;
}
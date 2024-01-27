/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and run premake

*/

#include "raylib.h"
#include "Game.h"

const int windowX = 960;
const int windowY = 600;
const int tileSize = 64;

void InitGame()
{
	//set up game grid
	auto gameGrid = Grid(300, 150, 5, 3, tileSize);
	Game::LoadGame(windowX, windowY, tileSize, gameGrid);
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
	InitWindow(windowX, windowY, "Tenes");
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

	SceneManager::Cleanup();
	CleanRaylib();
	return 0;
}
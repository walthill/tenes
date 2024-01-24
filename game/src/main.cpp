/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and run premake

*/

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

void update()
{
	SceneManager::UpdateScene();
}

void render()
{
	// drawing
	BeginDrawing();

	SceneManager::DrawScene();

	EndDrawing();
}

void initRaylib()
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

void cleanRaylib()
{
	// cleanup
	CloseAudioDevice();
	CloseWindow();
}

int main()
{
	initRaylib();

#ifdef NDEBUG
	SceneManager::SetScene(LOGO);
#elif DEBUG 
	SceneManager::SetScene(GAMEPLAY);
#endif // !NDEBUG

	InitGame();

	// game loop
	while (!WindowShouldClose())
	{
		update();
		render();
	}

	SceneManager::Cleanup();
	cleanRaylib();
	return 0;
}
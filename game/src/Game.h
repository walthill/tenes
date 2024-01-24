#ifndef GAME_H
#define GAME_H

#include "grid\Grid.h"
#include "scene\SceneManager.h"

#define GM Game::gameInstance

class Game
{
public:
	static Game* gameInstance;
	static void LoadGame(int a_windowX, int windowY, int tileSize, Grid a_grid);

	void Update();
	void Render();

	//Game Defines
	int windowX;
	int windowY;
	int tileSize;
	Grid gameGrid;
};

#endif
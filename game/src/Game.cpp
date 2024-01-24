#include "Game.h"

Game* Game::gameInstance = new Game;

void Game::LoadGame(int a_windowX, int a_windowY, int a_tileSize,
			Grid a_grid)
{
	auto inst = GM;

	//stats
	inst->windowX = a_windowX;
	inst->windowY = a_windowY;
	inst->tileSize = a_tileSize;
	
	//objects
	inst->gameGrid = a_grid;
}

void Game::Update()
{
	gameGrid.Update();
}

void Game::Render()
{
	gameGrid.Render();
}

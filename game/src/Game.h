#ifndef GAME_H
#define GAME_H

#include "scene\SceneManager.h"
#include "match\MatchPhaseDefines.h"
#include "ui\MatchUI.h"
#include "grid\Grid.h"

#define GM Game::gameInstance

enum class PhaseSubSection { None = 0, InitializePhase, Start, Update, UninitializePhase };

class Game
{
public:
	static Game* gameInstance;
	static void LoadGame(int a_windowX, int windowY, int tileSize, Grid a_grid);

	void Update();
	void Render();

	void SetNextPhase(MatchPhase* a_phase);
	void SetCurrentPhase(MatchPhase* a_phase);

	void LoadScene(GameScreen a_screen);

	//Game Defines
	int windowX;
	int windowY;
	int tileSize;
	Grid gameGrid;

private:

	bool m_changePhase;
	MatchPhase* mp_currentPhase;
	MatchPhase* mp_nextPhase;
	PhaseSubSection m_currentSubPhase;
	MatchUI m_matchUI;

	void UpdateMatchPhase();
	void RenderMatchPhase();
	void RenderUI();

};

#endif
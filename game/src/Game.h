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
	static void UnloadGame();

	~Game();

	void Update();
	void Render();

	void SetNextPhase(MatchPhase* a_phase);
	void SetCurrentPhase(MatchPhase* a_phase);

	void LoadScene(GameScreen a_screen);

	//UI Functions
	void IncrementTurnCount() { matchUI.IncrementTurnCount(); }
	void AddPiece(bool a_isPlayer);

	int DoDiceRoll(bool a_isPlayer);
	void ApplyPieceScored(bool a_isPlayer);
	void ApplyBonusMove(bool a_isPlayer);
	void ApplyBonusPoints(bool a_isPlayer);
	void IncrementBonusPointsCount() { m_scoreBonusHitCount++; }
	bool HasEarnedBonusPoints() { return m_scoreBonusHitCount == gameGrid.GetBonusPointsTileTargetHitCount(); }
	int GetBonusPointsCount() { return m_scoreBonusHitCount; }
	bool HasEnemyFinished();
	bool HasPlayerFinished();

	//Game Defines
	int windowX;
	int windowY;
	int tileSize;
	Grid gameGrid;
	MatchUI matchUI;

private:
	const int c_defaultMinRollAmount = 0;
	const int c_defaultMaxRollAmount = 2;
	const int c_numPieces = 2;
	const int c_bonusRollAmount = 2;
	const int c_bonusPointsAmount = 1000;
	const int c_firstPieceScoreAmount = 1000;
	const int c_addPieceScoreBonus = (int)(c_firstPieceScoreAmount * 0.25f);
	const int c_secondPieceScoreAmount = (int)(c_firstPieceScoreAmount * 0.5f);

	bool m_changePhase;
	MatchPhase* mp_currentPhase = nullptr;
	MatchPhase* mp_nextPhase = nullptr;
	PhaseSubSection m_currentSubPhase;

	int m_scoreBonusHitCount = 0;

	bool m_playerNextRollBonus = false;
	bool m_firstPlayerPieceScored = false;
	bool m_playerMovingFirstPiece = true;
	int m_playerScore = 0;

	bool m_enemyNextRollBonus = false;
	bool m_firstEnemyPieceScored = false;
	bool m_enemyMovingFirstPiece = true;
	int m_enemyScore = 0;

	void UpdateMatchPhase();
	void RenderMatchPhase();
	void RenderUI();

};

#endif
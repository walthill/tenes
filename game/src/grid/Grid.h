#ifndef GRID_H
#define GRID_H

#include "raymath.h"
#include <vector>
#include "Piece.h"

/*
	Game State Flow

	Player Roll,

	Player Move, 

	Enemy Roll, 

	Enemy Move

*/

enum class TileType { NIL = -1, BASE = 0, MOVE_BONUS, PIECE_BONUS, POINTS_BONUS };

struct Tile
{
	Vector2 pos;
	bool hasPlayer;
	bool hasEnemy;
	TileType type;

	inline bool IsEmpty() { return !hasPlayer && !hasEnemy; }
};

class Grid
{
public:
	Grid();
	Grid(float a_PosX, float a_PosY, int a_numRows, int a_numCols, int a_tileSize);

	void InitBonusTiles();

	void Update();
	void Render();

	Vector2 Get2DCoordsFromPos(Vector2 a_pos);
	int GetTileIndexFromPos(float a_x, float a_y);
	int GetTileIndexFromPos(Vector2 a_pos);
	Tile* GetTileFromPos(float a_x, float a_y);
	Tile* GetTileFromPos(Vector2 a_pos);
	Tile* GetTileFromIndex(int a_index);
	inline int GetWidth() { return m_width; };
	inline int GetHeight() { return m_height; };
	inline Piece* GetPlayerPiece(bool a_firstPiece) { return &m_playerPieces[a_firstPiece ? 0 : 1]; }
	inline Piece* GetEnemyPiece(bool a_firstPiece) { return &m_enemyPieces[a_firstPiece ? 0 : 1]; }
	inline bool PlayerHasSecondPiece() { return m_playerPieces[1].IsVisible(); };
	inline bool EnemyHasSecondPiece() { return m_enemyPieces[1].IsVisible(); };
	const Piece* GetPlayerPieces() { return m_playerPieces; }
	const Piece* GetEnemyPieces() { return m_enemyPieces; }

	bool MovePlayer(bool a_forward, int a_moveDistance, bool a_firstPiece);
	bool MoveEnemy(bool a_forward, int a_moveDistance, bool a_firstPiece);

	void AddPlayerPiece();
	void AddEnemyPiece();

	int GetBonusPointsTileTargetHitCount() { return m_bonusPointsTileTargetHitCount; }
	void BonusPointsAwarded(bool a_isPlayer);
	bool AlreadyAwardedBonusPoints() { return m_bonusPointTileAwarded; }
	void ReturnToRowStart(int a_rowIndex, bool a_isPlayer, bool a_firstPiece);

private:
	bool m_renderDebug = false;
	std::vector<Tile> m_gridList;
	int m_tileSize;
	int m_width;
	int m_height;
	
	Piece m_playerPieces[2];
	Piece m_enemyPieces[2];

	bool m_bonusPointTileAwarded = false;
	int m_bonusPointsTileTargetHitCount = 3;

	void RenderTiles();
	void RenderPieces();
	void CheckPieceSwapPlayer(int a_destinationIndex);
	void CheckPieceSwapEnemy(int a_destinationIndex);
	void CheckForPlayerPieceScore(int a_destinationIndex, bool a_firstPiece);
	void CheckForEnemyPieceScore(int a_destinationIndex, bool a_firstPiece);
};

#endif // !GRID_H

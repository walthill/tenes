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

enum class TileType { NIL = -1, BASE = 0, PLAYER, ENEMY };

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
		
		void Update();
		void Render();

		void RenderTiles();
		Vector2 Get2DCoordsFromPos(Vector2 a_pos);
		int GetTileIndexFromPos(float a_x, float a_y);
		int GetTileIndexFromPos(Vector2 a_pos);
		Tile* GetTileFromPos(float a_x, float a_y);
		Tile* GetTileFromPos(Vector2 a_pos);
		inline int GetWidth() { return m_width; };
		inline int GetHeight() { return m_height; };
		inline Piece* GetPlayerPiece() { return &m_playerPiece; }

		bool MovePlayer(bool a_forward, int a_moveDistance);
		bool MoveEnemy(bool a_forward, int a_moveDistance);
		bool HasEnemyWon();
		bool HasPlayerWon();

	private:
		bool m_renderDebug = false;
		std::vector<Tile> m_gridList;
		int m_tileSize;
		int m_width;
		int m_height;
		Piece m_playerPiece;
		Piece m_enemyPiece;

		void CheckPieceSwapPlayer(int a_initialIndex, int a_destinationIndex);
		void CheckPieceSwapEnemy(int a_initialIndex, int a_destinationIndex);
};

#endif // !GRID_H

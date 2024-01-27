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

enum class TileType { NIL = -1, BASE = 0, };

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
		int GetWidth() { return m_width; };
		int GetHeight() { return m_height; };

	private:
		bool m_renderDebug = false;
		std::vector<Tile> m_gridList;
		int m_tileSize;
		int m_width;
		int m_height;
		Piece m_playerPiece;
		Piece m_enemyPiece;
};

#endif // !GRID_H

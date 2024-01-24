#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "raymath.h"
#include <vector>

struct Tile
{
	Vector2 pos;
};

class Grid
{
	public:
		Grid();
		Grid(float a_PosX, float a_PosY, int a_numRows, int a_numCols, int a_tileSize);
		
		void Update();
		void Render();

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
};

#endif // !GRID_H

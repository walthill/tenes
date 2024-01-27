#include "raylib.h"
#include "Grid.h"

Grid::Grid() :
	m_height(0), m_width(0), m_tileSize(0), m_renderDebug(false)
{
}

Grid::Grid(float a_PosX, float a_PosY, int a_numRows, int a_numCols, int a_tileSize)
{
	m_renderDebug = false;
	m_gridList = std::vector<Tile>();
	m_tileSize = a_tileSize;
	m_width = a_numRows;	//rows
	m_height = a_numCols;	//cols
	
	for (size_t i = 0; i < m_height; i++)
	{
		for (size_t k = 0; k < m_width; k++)
		{
			auto x = (float)k * a_tileSize + a_PosX;
			auto y = (float)i * a_tileSize + a_PosY;
			auto tile = Tile({x,y});
			m_gridList.push_back(tile);
		}
	}

	m_playerPiece = Piece(5, true, 0);
	m_enemyPiece = Piece(5, false, 1);

	m_gridList[0].type = TileType::PLAYER;
	m_gridList[1].type = TileType::ENEMY;
}

void Grid::Update()
{
#if _DEBUG
	if (IsKeyPressed(KEY_G))
		m_renderDebug = !m_renderDebug;
#endif
}

void Grid::Render()
{
#if _DEBUG
	if (m_renderDebug)
	{
		auto count = m_gridList.size();
		for (size_t i = 0; i < count; i++)
		{
			auto tile = m_gridList[i];
			DrawRectangleLines((int)tile.pos.x, (int)tile.pos.y, m_tileSize, m_tileSize, BLACK);
		}
	}
#endif

	RenderTiles();
}

void Grid::RenderTiles()
{
	auto count = m_gridList.size();
	for (size_t i = 0; i < count; i++)
	{
		auto tile = m_gridList[i];
		
		auto tileColor = GRAY;
		switch (tile.type)
		{
			case TileType::NIL:			tileColor = MAGENTA;	break;
			case TileType::BASE:		tileColor = GRAY;		break;
			case TileType::PLAYER:		tileColor = GOLD;		break;
			//case TileType::ENEMY:		tileColor = MAROON;		break;
		}

		DrawRectangle((int)tile.pos.x, (int)tile.pos.y, m_tileSize, m_tileSize, tileColor);
	}
}

Vector2 Grid::Get2DCoordsFromPos(Vector2 a_pos)
{
	int row = (int)(roundf(a_pos.x) / m_tileSize);
	int col = (int)(roundf(a_pos.y) / m_tileSize);
	return { (float)row, (float)col };
}

int Grid::GetTileIndexFromPos(float a_x, float a_y)
{
	//turn position into grid
	int row = (int)(roundf(a_x) / m_tileSize);
	int col = (int)(roundf(a_y) / m_tileSize);
	int index = col + (row * m_height);
	return index;
}

int Grid::GetTileIndexFromPos(Vector2 a_pos)
{
	return GetTileIndexFromPos(a_pos.x, a_pos.y);
}

Tile* Grid::GetTileFromPos(float a_x, float a_y)
{
	//turn position into grid
	int row = (int)(roundf(a_x) / m_tileSize);
	int col = (int)(roundf(a_y) / m_tileSize);
	int index = col + (row * m_height);

	if (index >= m_gridList.size())
		return &m_gridList[m_gridList.size() - 1];

	return &m_gridList[index];
}

Tile* Grid::GetTileFromPos(Vector2 a_pos)
{
	return GetTileFromPos(a_pos.x, a_pos.y);
}

void Grid::MovePlayer(bool a_forward, int a_moveDistance)
{
	if (a_moveDistance == 0)
		return;

	auto initialIndex = m_playerPiece.GetBoardIndex();
	if (a_forward)
	{
		auto moveIndex = initialIndex + a_moveDistance;
		if (moveIndex < m_gridList.size())
		{
			m_gridList[moveIndex].type = TileType::PLAYER;
			m_playerPiece.SetBoardIndex(moveIndex);
			m_gridList[initialIndex].type = TileType::BASE;
		}
	}
	else
	{
		auto moveIndex = initialIndex - a_moveDistance;
		if (moveIndex >= 0)
		{
			m_gridList[moveIndex].type = TileType::PLAYER;
			m_playerPiece.SetBoardIndex(moveIndex);
			m_gridList[initialIndex].type = TileType::BASE;
		}
	}
}

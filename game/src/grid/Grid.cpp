#include "raylib.h"
#include "Grid.h"
#include <random>
#include "Game.h"

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
	
	//TODO: make pieces objects that are rendered to the screen
	//m_playerPiece.SetPosition

	m_enemyPiece = Piece(5, false, 1);

	InitBonusTiles();

}

void Grid::InitBonusTiles() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, m_width - 1);

	int randomIndex = dis(gen);
	m_gridList[randomIndex].type = TileType::MOVE_BONUS;

	randomIndex = dis(gen) + m_width;
	m_gridList[randomIndex].type = TileType::PIECE_BONUS;

	m_gridList[m_gridList.size() - 1].type = TileType::POINTS_BONUS;
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
	RenderTiles();
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
			case TileType::NIL:				tileColor = MAGENTA;	break;
			case TileType::BASE:			tileColor = GRAY;		break;
			case TileType::MOVE_BONUS:		tileColor = GREEN;		break;
			case TileType::PIECE_BONUS:		tileColor = BLUE;		break;
			case TileType::POINTS_BONUS:	tileColor = BLACK;		break;
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

Tile* Grid::GetTileFromIndex(int a_index)
{
	return &m_gridList[a_index];
}

bool Grid::MovePlayer(bool a_forward, int a_moveDistance)
{
	if (a_moveDistance == 0)
		return false;

	auto initialIndex = m_playerPiece.GetBoardIndex();
	if (a_forward)
	{
		auto moveIndex = initialIndex + a_moveDistance;
		if (moveIndex < m_gridList.size())
		{
			CheckPieceSwapEnemy(initialIndex, moveIndex);

			//TODO: update piece movement
			//m_gridList[moveIndex].type = TileType::PLAYER;
			m_playerPiece.SetBoardIndex(moveIndex);
		}
	}
	else
	{
		auto moveIndex = initialIndex - a_moveDistance;
		if (moveIndex >= 0)
		{
			CheckPieceSwapEnemy(initialIndex, moveIndex);

			//TODO: update piece movement
			//m_gridList[moveIndex].type = TileType::PLAYER;
			m_playerPiece.SetBoardIndex(moveIndex);
		}
	}

	return true;
}

bool Grid::MoveEnemy(bool a_forward, int a_moveDistance)
{
	if (a_moveDistance == 0)
		return false;

	auto initialIndex = m_enemyPiece.GetBoardIndex();
	if (a_forward)
	{
		auto moveIndex = initialIndex + a_moveDistance;
		if (moveIndex < m_gridList.size())
		{
			CheckPieceSwapPlayer(initialIndex, moveIndex);

			//TODO: update piece movement
			//m_gridList[moveIndex].type = TileType::ENEMY;
			m_enemyPiece.SetBoardIndex(moveIndex);
		}
	}
	else
	{
		auto moveIndex = initialIndex - a_moveDistance;
		if (moveIndex >= 0)
		{
			CheckPieceSwapPlayer(initialIndex, moveIndex);

			//TODO: update piece movement
			//m_gridList[moveIndex].type = TileType::ENEMY;
			m_enemyPiece.SetBoardIndex(moveIndex);
		}
	}

	return true;
}

bool Grid::HasEnemyWon()
{
	return m_enemyPiece.GetBoardIndex() == m_gridList.size() - 1;
}

bool Grid::HasPlayerWon()
{
	return m_playerPiece.GetBoardIndex() == m_gridList.size() - 1;
}

void Grid::BonusPointsAwarded()
{
	m_bonusPointTileAwarded = true;
}

void Grid::CheckPieceSwapEnemy(int a_initialIndex, int a_destinationIndex)
{
	//TODO: update piece movement
	if (m_gridList[a_destinationIndex].type == TileType::NIL)
	{
		//move enemy to player's start position
		m_enemyPiece.SetBoardIndex(a_initialIndex);
		//TODO: update piece movement
		//m_gridList[a_initialIndex].type = TileType::ENEMY;
	}
	else
	{
		//TODO: update piece movement
		m_gridList[a_initialIndex].type = TileType::BASE;
	}
}


void Grid::CheckPieceSwapPlayer(int a_initialIndex, int a_destinationIndex)
{
	//TODO: update piece movement
	if (m_gridList[a_destinationIndex].type == TileType::NIL)
	{
		//move player to enemy's start position
		m_playerPiece.SetBoardIndex(a_initialIndex);
		
		//m_gridList[a_initialIndex].type = TileType::PLAYER;
	}
	else
	{
		m_gridList[a_initialIndex].type = TileType::BASE;
	}
}

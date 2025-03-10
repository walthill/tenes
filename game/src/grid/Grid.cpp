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

	m_playerStartPos1 = { 25.0f, 180.0f };
	m_playerStartPos2 = { 25.0f, 180.0f + Piece::PieceSize + 16 };
	m_enemyStartPos1 = { (float)GetScreenWidth() - 100.0f, 180.0f };
	m_enemyStartPos2 = { (float)GetScreenWidth() - 100.0f, 180.0f + Piece::PieceSize + 16 };

	m_playerPieces[0] = Piece(true, -1);
	m_playerPieces[0].SetPosition(m_playerStartPos1);
	m_playerPieces[1] = Piece(true, -1);
	m_playerPieces[1].SetPosition(m_playerStartPos2);
	m_playerPieces[1].SetVisible(false);
	m_enemyPieces[0] = Piece(false, -1);
	m_enemyPieces[0].SetPosition(m_enemyStartPos1);
	m_enemyPieces[1] = Piece(false, -1);
	m_enemyPieces[1].SetPosition(m_enemyStartPos2);
	m_enemyPieces[1].SetVisible(false);

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

	m_gridList[m_gridList.size() - 2].type = TileType::POINTS_BONUS;
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
	RenderPieces();
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

void Grid::RenderPieces() {
	for each(auto piece in m_playerPieces)
	{
		piece.Render();
	}

	for each(auto piece in m_enemyPieces)
	{
		piece.Render();
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

//TODO: lerp/animate the movement
bool Grid::MovePlayer(bool a_forward, int a_moveDistance, bool a_firstPiece)
{
	auto playerPiece = GetPlayerPiece(a_firstPiece);
	if (!playerPiece->IsMoving()) {
		if (a_moveDistance == 0)
			return false;

		auto initialIndex = playerPiece->GetBoardIndex();
		m_moveIndex = a_forward ? initialIndex + a_moveDistance : initialIndex - a_moveDistance;

		if (m_moveIndex < 0 || m_moveIndex >= m_gridList.size())
			return false;

		std::vector<Vector2> path;
		int step = a_forward ? 1 : -1;
		for (int i = initialIndex + step; i != m_moveIndex + step; i += step)
		{
			auto pos = m_gridList[i].pos;
			pos.x += m_tileSize * 0.5f;
			pos.y += m_tileSize * 0.5f;
			pos.x -= Piece::PieceSize * 0.5f;
			pos.y -= Piece::PieceSize * 0.5f;
			path.push_back(pos);
		}

		playerPiece->StartMovement(m_moveIndex, path);
	}
	else
	{
		auto moveDone = playerPiece->Move();
		if (moveDone) {
			CheckPieceSwapEnemy(m_moveIndex);
			CheckForPlayerPieceScore(m_moveIndex, a_firstPiece);

		}
		return moveDone;
	}

	return false;
}

bool Grid::MoveEnemy(bool a_forward, int a_moveDistance, bool a_firstPiece)
{
	auto enemyPiece = GetEnemyPiece(a_firstPiece);
	if (!enemyPiece->IsMoving()) {
		if (a_moveDistance == 0)
			return false;

		auto initialIndex = enemyPiece->GetBoardIndex();
		m_moveIndex = a_forward ? initialIndex + a_moveDistance : initialIndex - a_moveDistance;

		if (m_moveIndex < 0 || m_moveIndex >= m_gridList.size())
			return false;
		std::vector<Vector2> path;
		int step = a_forward ? 1 : -1;
		for (int i = initialIndex + step; i != m_moveIndex + step; i += step)
		{
			auto pos = m_gridList[i].pos;
			pos.x += m_tileSize * 0.5f;
			pos.y += m_tileSize * 0.5f;
			pos.x -= Piece::PieceSize * 0.5f;
			pos.y -= Piece::PieceSize * 0.5f;
			path.push_back(pos);
		}
		enemyPiece->StartMovement(m_moveIndex, path);
	}
	else
	{
		auto moveDone = enemyPiece->Move();
		if (moveDone) {
			CheckPieceSwapPlayer(m_moveIndex);
			CheckForEnemyPieceScore(m_moveIndex, a_firstPiece);
		}
		return moveDone;
	}

	return false;
}

//TODO: support cases where the first piece is returned to the start while the second piece is still on the board (add visual diff between first and second piece?)
void Grid::AddPlayerPiece()
{
	m_playerPieces[1].SetVisible(true);
	GM->AddPiece(true);
}

void Grid::AddEnemyPiece()
{
	m_enemyPieces[1].SetVisible(true);
	GM->AddPiece(false);
}

void Grid::BonusPointsAwarded(bool a_isPlayer)
{
	m_bonusPointTileAwarded = true;
}

void Grid::ReturnToRowStart(int a_rowIndex, bool a_isPlayer, bool a_firstPiece)
{
	Piece* piece = nullptr;
	if(a_isPlayer)
		piece = GetPlayerPiece(a_firstPiece);
	else
		piece = GetEnemyPiece(a_firstPiece);

	piece->SetBoardIndex(m_width * a_rowIndex);
	Vector2 newPos = m_gridList[m_width * a_rowIndex].pos;
	newPos.x += m_tileSize * 0.5f;
	newPos.y += m_tileSize * 0.5f;
	newPos.x -= Piece::PieceSize * 0.5f;
	newPos.y -= Piece::PieceSize * 0.5f;
	piece->SetPosition(newPos);
}

bool Grid::CanMovePlayerPiece(int a_rollAmount, bool a_forward, bool a_firstPiece)
{
	auto playerPiece = GetPlayerPiece(a_firstPiece);
	auto index = playerPiece->GetBoardIndex();
	return a_forward ? index + a_rollAmount <= m_gridList.size() - 1
		: index - a_rollAmount >= 0;
}

void Grid::CheckPieceSwapEnemy(int a_destinationIndex)
{
	for (size_t i = 0; i < 2; i++)
	{
		auto& enemyPiece = m_enemyPieces[i];
		if (enemyPiece.GetBoardIndex() == a_destinationIndex)
		{
			enemyPiece.SetBoardIndex(-1);
			enemyPiece.SetPosition({ (float)GetScreenWidth() - 100.0f, 180.0f + ((Piece::PieceSize + 16) * i) });
		}
	}
}

void Grid::CheckPieceSwapPlayer(int a_destinationIndex)
{
	for (size_t i = 0; i < 2; i++)
	{
		auto& playerPiece = m_playerPieces[i];
		if (playerPiece.GetBoardIndex() == a_destinationIndex)
		{
			playerPiece.SetBoardIndex(-1);
			playerPiece.SetPosition({ 25.0f, 180.0f + ((Piece::PieceSize + 16) * i) });
		}
	}
}

void Grid::CheckForPlayerPieceScore(int a_destinationIndex, bool a_firstPiece)
{
	if (a_destinationIndex != m_gridList.size() - 1)
		return;

	GM->ApplyPieceScored(true);
	auto playerPiece = GetEnemyPiece(a_firstPiece);
	playerPiece->SetBoardIndex(-1);
	playerPiece->SetVisible(false);
}

void Grid::CheckForEnemyPieceScore(int a_destinationIndex, bool a_firstPiece)
{
	if(a_destinationIndex != m_gridList.size() - 1)
		return;

	GM->ApplyPieceScored(false);
	auto enemyPiece = GetEnemyPiece(a_firstPiece);
	enemyPiece->SetBoardIndex(-1);
	enemyPiece->SetVisible(false);

}

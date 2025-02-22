#include "raylib.h"
#include "Piece.h"

Piece::Piece() :
	m_isPlayer(false),
	m_scored(false),
	m_visible(true),
	m_boardIndex(0)
{
}

Piece::Piece(bool a_isPlayer, int a_boardIndex)
{
	m_isPlayer = a_isPlayer;
	m_boardIndex = a_boardIndex;
	m_scored = false;
	m_visible = true;
}

void Piece::Update()
{
}

void Piece::Render()
{
	if(!m_visible)
		return;

	DrawRectangle((int)m_position.x, (int)m_position.y, PieceSize, PieceSize, m_isPlayer ? GOLD : MAROON);
}

void Piece::SetBoardIndex(int a_index)
{
	m_boardIndex = a_index;
}

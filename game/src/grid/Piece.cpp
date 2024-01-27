#include "raylib.h"
#include "Piece.h"

Piece::Piece() :
	m_lives(0), m_isPlayer(false), 
	m_boardIndex(0)
{
}

Piece::Piece(int a_lives, bool a_isPlayer, int a_boardIndex)
{
	m_lives = a_lives;
	m_isPlayer = a_isPlayer;
	m_boardIndex = a_boardIndex;
}

void Piece::SetBoardIndex(int a_index)
{
	m_boardIndex = a_index;
}

#include "raylib.h"
#include "Piece.h"

Piece::Piece() :
	m_lives(0), m_isPlayer(false)
{
}

Piece::Piece(int a_lives, bool a_isPlayer)
{
	m_lives = a_lives;
	m_isPlayer = a_isPlayer;
}

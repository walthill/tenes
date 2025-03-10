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

void Piece::StartMovement(int a_index, const std::vector<Vector2>& a_path)
{
	SetBoardIndex(a_index);
	m_startPos = GetPosition();
    m_path = a_path;
	m_currentPathIndex = 0;
	m_endPos = m_path[m_currentPathIndex];
	m_elapsedTime = 0.0f;
	m_isMoving = true;
}

bool Piece::Move()
{
    m_elapsedTime += GetFrameTime();
    float t = m_elapsedTime / m_duration;
    if (t >= 1.0f)
    {
        t = 1.0f;
        m_position = m_endPos;
        m_elapsedTime = 0.0f;
        m_currentPathIndex++;
        if (m_currentPathIndex < m_path.size())
        {
            m_startPos = m_position;
            m_endPos = m_path[m_currentPathIndex];
        }
        else
        {
            m_isMoving = false;
        }
    }
    else
    {
        m_position = Vector2Lerp(m_startPos, m_endPos, t);
    }

    return !m_isMoving;
}
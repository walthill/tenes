#include "raylib.h"
#include "PlayerTurnPhase.h"
#include "Game.h"
#include <grid/Piece.h>

PlayerTurnPhase::PlayerTurnPhase()
{
	m_waitAfterRollTime = 2.0f;
	m_timer = 0;
	m_rollComplete = false;
	m_rollAmount = 0;
}

bool PlayerTurnPhase::Initialize()
{
	MatchPhase::Initialize();
	return true;
}

void PlayerTurnPhase::Start()
{
}

void PlayerTurnPhase::Update()
{
	if (!m_rollComplete)
	{
		DrawText("ROLL", 400, 100, 36, BLACK);
		if (IsKeyPressed(KEY_SPACE))
		{
			m_rollAmount = GetRandomValue(0, 2);
			auto amountStr = "Player Move -- Roll Amount: " + std::to_string(m_rollAmount);
			TraceLog(LOG_TRACE, amountStr.c_str());
			m_rollComplete = true;
		}
	}
	else
	{
		if(m_timer < m_waitAfterRollTime)
			m_timer += GetFrameTime();
		else
		{
			if (m_rollAmount > 0)
			{
				if (IsKeyPressed(KEY_E))
				{
					auto amountStr = "Player Move -- Forward: " + std::to_string(m_rollAmount);
					TraceLog(LOG_TRACE, amountStr.c_str());
					GM->gameGrid.MovePlayer(true, m_rollAmount);
					//TODO: Start enemy phase
				}
				else if (IsKeyPressed(KEY_Q))
				{
					auto amountStr = "Player Move -- Back: " + std::to_string(m_rollAmount);
					TraceLog(LOG_TRACE, amountStr.c_str());
					GM->gameGrid.MovePlayer(false, m_rollAmount);
					//TODO: Start enemy phase
				}
			}
			else
			{
				//TODO: Start enemy phase
			}
		}
	}
}

void PlayerTurnPhase::Render()
{
	if (!m_rollComplete)
		DrawText("YOUR ROLL", 400, 100, 36, BLACK);
	else if(m_rollComplete && m_rollAmount > 0)
		DrawText("YOUR MOVE", 400, 100, 36, BLACK);
}

bool PlayerTurnPhase::Uninitialize()
{
	MatchPhase::Uninitialize();
	return true;
}

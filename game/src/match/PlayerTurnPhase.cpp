#include "raylib.h"
#include "PlayerTurnPhase.h"
#include "Game.h"

PlayerTurnPhase::PlayerTurnPhase()
{
	m_waitAfterRollTime = 1.0f;
	m_timeToEndTurn = 2.0f;
	m_timer = 0;
	m_rollComplete = false;
	m_rollAmount = 0;
	m_turnEnd = false;
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
	if (m_turnEnd)
	{
		if (m_timer < m_timeToEndTurn)
			m_timer += GetFrameTime();
		else
		{
			m_timer = 0;
			if (!GM->gameGrid.HasPlayerWon())
				GM->SetNextPhase(new EnemyTurnPhase());
			else 
			{
				//TODO: win condition
				GM->LoadScene(ENDING);
			}
		}
		return;
	}

	if (!m_rollComplete)
	{
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
					if (GM->gameGrid.MovePlayer(true, m_rollAmount))
					{
						m_turnEnd = true;
						m_timer = 0.0f;
					}
				}
				else if (IsKeyPressed(KEY_Q))
				{
					auto amountStr = "Player Move -- Back: " + std::to_string(m_rollAmount);
					TraceLog(LOG_TRACE, amountStr.c_str());
					if (GM->gameGrid.MovePlayer(false, m_rollAmount))
					{
						m_turnEnd = true;
						m_timer = 0.0f;
					}
				}
			}
			else
			{
				m_turnEnd = true;
				m_timer = 0.0f;
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

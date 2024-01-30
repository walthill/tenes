#include "raylib.h"
#include "EnemyTurnPhase.h"
#include "Game.h"

EnemyTurnPhase::EnemyTurnPhase()
{
	m_timeUntilRoll = 2.0f;
	m_waitAfterRollTime = 2.0f;
	m_timer = 0;
	m_rollComplete = false;
	m_rollAmount = 0;
	m_turnEnd = false;
	m_timeToEndTurn = 2.0f;
}

bool EnemyTurnPhase::Initialize()
{
	MatchPhase::Initialize();
	return true;
}

void EnemyTurnPhase::Start()
{
}

void EnemyTurnPhase::Update()
{
	if (m_turnEnd)
	{
		if (m_timer < m_timeToEndTurn)
			m_timer += GetFrameTime();
		else
		{
			if(!GM->gameGrid.HasEnemyWon())
				GM->SetNextPhase(new PlayerTurnPhase());
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
		if (m_timer < m_timeUntilRoll)
			m_timer += GetFrameTime();
		else
		{
			m_timer = 0;
			m_rollAmount = GetRandomValue(0, 2);
			auto amountStr = "Enemy Move -- Roll Amount: " + std::to_string(m_rollAmount);
			TraceLog(LOG_TRACE, amountStr.c_str());
			m_rollComplete = true;
		}
	}
	else
	{
		if (m_timer < m_waitAfterRollTime)
			m_timer += GetFrameTime();
		else
		{
			m_timer = 0;
			if (m_rollAmount > 0)
			{
				//TODO: how should the AI decide which direction to move? 
				//for now just move forward

				auto amountStr = "Enemy Move -- Forward: " + std::to_string(m_rollAmount);
				TraceLog(LOG_TRACE, amountStr.c_str());
				GM->gameGrid.MoveEnemy(true, m_rollAmount);
			}
			m_turnEnd = true;
		}
	}
}

void EnemyTurnPhase::Render()
{
	if (!m_rollComplete)
		DrawText("CPU ROLL", 400, 100, 36, BLACK);
	else if (m_rollComplete)
		DrawText("CPU MOVE", 400, 100, 36, BLACK);
}

bool EnemyTurnPhase::Uninitialize()
{
	MatchPhase::Uninitialize();
	return true;
}

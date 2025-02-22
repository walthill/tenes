#include "raylib.h"
#include "EnemyTurnPhase.h"
#include "Game.h"
#include <string>

EnemyTurnPhase::EnemyTurnPhase()
{
	m_timeUntilRoll = 1.33f;
	m_waitAfterRollTime = 1.33f;
	m_timer = 0;
	m_rollComplete = false;
	m_rollAmount = 0;
	m_turnEnd = false;
	m_timeToEndTurn = 1.33f;
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
			if (!GM->HasEnemyFinished() || !GM->HasPlayerFinished()) {
				GM->SetNextPhase(new PlayerTurnPhase());
				GM->IncrementTurnCount();
			}
			else
			{
				GM->LoadScene(ENDING);
			}
		}

		return;
	}

	if (!m_rollComplete)
	{
		if (GM->HasEnemyFinished())
		{
			m_turnEnd = true;
		}

		if (m_timer < m_timeUntilRoll)
			m_timer += GetFrameTime();
		else
		{
			m_timer = 0;
			m_rollAmount = GM->DoDiceRoll(false);
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
				//TODO: how should the AI decide which direction and which piece to move? 
				//for now just move forward on a random piece

				if (GM->gameGrid.EnemyHasSecondPiece() && GetRandomValue(0, 1) == 0)
				{
					m_movingFirstPiece = false;
				}
				else
				{
					m_movingFirstPiece = true;
				}
				
				auto amountStr = "Enemy Move -- Forward: " + std::to_string(m_rollAmount);
				TraceLog(LOG_TRACE, amountStr.c_str());
				GM->gameGrid.MoveEnemy(true, m_rollAmount, m_movingFirstPiece);
				CheckForBonusTile();
			}
			m_turnEnd = true;
		}
	}
}

void EnemyTurnPhase::Render()
{
	if (!m_rollComplete)
	{
		DrawText("CPU ROLL", 350, 100, 36, BLACK);
	}
	else if (m_rollComplete)
	{
		auto amtStr = std::to_string(m_rollAmount);
		DrawText(("CPU MOVE (" + amtStr + ")").c_str(), 350, 100, 36, BLACK);
	}
}

bool EnemyTurnPhase::Uninitialize()
{
	MatchPhase::Uninitialize();
	return true;
}

void EnemyTurnPhase::CheckForBonusTile()
{
	auto piece = GM->gameGrid.GetEnemyPiece(m_movingFirstPiece);
	auto tile = GM->gameGrid.GetTileFromIndex(piece->GetBoardIndex());
	switch (tile->type)
	{
		case TileType::MOVE_BONUS:		ApplyBonusMove(); break;
		case TileType::PIECE_BONUS:		ApplyBonusPiece(); break;
		case TileType::POINTS_BONUS:	ApplyBonusPoints(); break;
		default: break;
	}
}

void EnemyTurnPhase::ApplyBonusMove()
{
	TraceLog(LOG_TRACE, "Enemy Move Bonus");
	GM->ApplyBonusMove(false);
}

void EnemyTurnPhase::ApplyBonusPiece()
{
	TraceLog(LOG_TRACE, "Enemy Piece Bonus");
	GM->gameGrid.AddEnemyPiece();
}

void EnemyTurnPhase::ApplyBonusPoints()
{
	if (GM->gameGrid.AlreadyAwardedBonusPoints())
		return;

	TraceLog(LOG_TRACE, "Enemy Points Bonus");

	GM->IncrementBonusPointsCount(false);
	if (GM->HasEarnedBonusPoints(false))
	{
		TraceLog(LOG_TRACE, "Apply Enemy Points Bonus");
		GM->ApplyBonusPoints(false);
	}
}

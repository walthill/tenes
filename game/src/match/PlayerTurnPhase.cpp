#include "raylib.h"
#include "PlayerTurnPhase.h"
#include "Game.h"

PlayerTurnPhase::PlayerTurnPhase()
{
	m_waitAfterRollTime = 1.33f;
	m_timeToEndTurn = 1.33f;
	m_rollComplete = false;
	m_rollAmount = 0;
	m_timer = 0;
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
			if (!GM->HasPlayerFinished())	//cpu forfeits if player wins
				GM->SetNextPhase(new EnemyTurnPhase());
			else 
			{
				GM->LoadScene(ENDING);
			}
		}
		return;
	}

	if (!m_rollComplete)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			m_rollAmount = GM->DoDiceRoll(true);
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
					auto moveForward = false;
					auto amountStr = "Player Move -- Forward: " + std::to_string(m_rollAmount);
					TraceLog(LOG_TRACE, amountStr.c_str());
					m_movingFirstPiece = true;
					if (GM->gameGrid.MovePlayer(true, m_rollAmount, m_movingFirstPiece))
					{
						CheckForBonusTile();
						m_turnEnd = true;
						m_timer = 0.0f;
					}
				}
				else if (IsKeyPressed(KEY_Q))
				{
					auto amountStr = "Player Move -- Back: " + std::to_string(m_rollAmount);
					TraceLog(LOG_TRACE, amountStr.c_str());
					m_movingFirstPiece = true;
					if (GM->gameGrid.MovePlayer(false, m_rollAmount, m_movingFirstPiece))
					{
						CheckForBonusTile();
						m_turnEnd = true;
						m_timer = 0.0f;
					}
				}

				if (GM->gameGrid.PlayerHasSecondPiece()) 
				{
					if (IsKeyPressed(KEY_D))
					{
						auto amountStr = "Player Move Piece 2-- Forward: " + std::to_string(m_rollAmount);
						TraceLog(LOG_TRACE, amountStr.c_str());
						m_movingFirstPiece = false;
						if (GM->gameGrid.MovePlayer(true, m_rollAmount, m_movingFirstPiece))
						{
							CheckForBonusTile();
							m_turnEnd = true;
							m_timer = 0.0f;
						}
					}
					else if (IsKeyPressed(KEY_A))
					{
						auto amountStr = "Player Move Piece 2 -- Back: " + std::to_string(m_rollAmount);
						TraceLog(LOG_TRACE, amountStr.c_str());
						m_movingFirstPiece = false;
						if (GM->gameGrid.MovePlayer(false, m_rollAmount, m_movingFirstPiece))
						{
							CheckForBonusTile();
							m_turnEnd = true;
							m_timer = 0.0f;
						}
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
	{
		DrawText("YOUR ROLL", 350, 100, 36, BLACK);
	}
	else if (m_rollComplete && m_rollAmount > 0)
	{
		auto amtStr = std::to_string(m_rollAmount);
		DrawText(("YOUR MOVE (" + amtStr + ")").c_str(), 350, 100, 36, BLACK);
	}
}

bool PlayerTurnPhase::Uninitialize()
{
	MatchPhase::Uninitialize();
	return true;
}

void PlayerTurnPhase::CheckForBonusTile()
{
	auto piece = GM->gameGrid.GetPlayerPiece(m_movingFirstPiece);
	auto tile = GM->gameGrid.GetTileFromIndex(piece->GetBoardIndex());
	switch (tile->type)
	{
		case TileType::MOVE_BONUS:		ApplyBonusMove(); break;
		case TileType::PIECE_BONUS:		ApplyBonusPiece(); break;
		case TileType::POINTS_BONUS:	ApplyBonusPoints(); break;
		default: break;
	}
}

void PlayerTurnPhase::ApplyBonusMove()
{
	TraceLog(LOG_TRACE, "Player Move Bonus");
	GM->ApplyBonusMove(true);
}

void PlayerTurnPhase::ApplyBonusPiece()
{
	TraceLog(LOG_TRACE, "Player Piece Bonus");
	GM->gameGrid.AddPlayerPiece();
}

void PlayerTurnPhase::ApplyBonusPoints()
{
	if (GM->gameGrid.AlreadyAwardedBonusPoints())
		return;

	TraceLog(LOG_TRACE, "Player Points Bonus");
	GM->IncrementBonusPointsCount(true);
	if (GM->HasEarnedBonusPoints(true))
	{
		TraceLog(LOG_TRACE, "Apply Player Points Bonus");
		GM->ApplyBonusPoints(true);
	}
}

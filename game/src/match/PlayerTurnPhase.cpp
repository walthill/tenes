#include "raylib.h"
#include "PlayerTurnPhase.h"
#include "Game.h"

PlayerTurnPhase::PlayerTurnPhase()
{
	m_waitAfterRollTime = 0.0f;
	m_timeToEndTurn = 1.0f;
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
				if (!m_pieceMoving)
				{
					if (IsKeyPressed(KEY_E) && GM->gameGrid.CanMovePlayerPiece(m_rollAmount, true, true))
					{
						auto amountStr = "Player Move -- Forward: " + std::to_string(m_rollAmount);
						TraceLog(LOG_TRACE, amountStr.c_str());
						m_movingFirstPiece = true;
						m_pieceMoving = true;
						m_moveForward = true;
					}
					else if (IsKeyPressed(KEY_Q) && GM->gameGrid.CanMovePlayerPiece(m_rollAmount, false, true))
					{
						auto amountStr = "Player Move -- Back: " + std::to_string(m_rollAmount);
						TraceLog(LOG_TRACE, amountStr.c_str());
						m_movingFirstPiece = true;
						m_pieceMoving = true;
						m_moveForward = false;
					}
					else if (GM->gameGrid.PlayerHasSecondPiece())
					{
						if (IsKeyPressed(KEY_C) && GM->gameGrid.CanMovePlayerPiece(m_rollAmount, true, false))
						{
							auto amountStr = "Player Move Piece 2-- Forward: " + std::to_string(m_rollAmount);
							TraceLog(LOG_TRACE, amountStr.c_str());
							m_movingFirstPiece = false;
							m_pieceMoving = true;
							m_moveForward = true;
						}
						else if (IsKeyPressed(KEY_Z) && GM->gameGrid.CanMovePlayerPiece(m_rollAmount, false, false))
						{
							auto amountStr = "Player Move Piece 2 -- Back: " + std::to_string(m_rollAmount);
							TraceLog(LOG_TRACE, amountStr.c_str());
							m_movingFirstPiece = false;
							m_pieceMoving = true;
							m_moveForward = false;
						}
					}
				}
				else
				{
					if (GM->gameGrid.MovePlayer(m_moveForward, m_rollAmount, m_movingFirstPiece))
					{
						CheckForBonusTile();
						m_turnEnd = true;
						m_timer = 0.0f;
						m_pieceMoving = false;
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
	if (GM->gameGrid.PlayerHasSecondPiece())
		return;

	TraceLog(LOG_TRACE, "Player Piece Bonus");
	GM->gameGrid.AddPlayerPiece();
}

void PlayerTurnPhase::ApplyBonusPoints()
{
	if (GM->gameGrid.AlreadyAwardedBonusPoints())
		return;

	TraceLog(LOG_TRACE, "Player Points Bonus");
	GM->IncrementBonusPointsCount();
	if (GM->HasEarnedBonusPoints())
	{
		TraceLog(LOG_TRACE, "Apply Player Points Bonus");
		GM->ApplyBonusPoints(true);
	} 
	else
	{
		GM->gameGrid.ReturnToRowStart(2, true, m_movingFirstPiece);
	}
}

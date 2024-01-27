#include "raylib.h"
#include "PlayerTurnPhase.h"
#include "Game.h"
#include <grid/Piece.h>
#include <string>

PlayerTurnPhase::PlayerTurnPhase()
{
}

bool PlayerTurnPhase::Initialize()
{
	return true;
}

void PlayerTurnPhase::Start()
{
}

void PlayerTurnPhase::Update()
{
	if (IsKeyPressed(KEY_E))
	{
		//TODO: separate out roll step from movement direction select

		int rollAmount = GetRandomValue(0, 2);
		auto amountStr = "Player Move -- Roll Amount: " + std::to_string(rollAmount);
		TraceLog(LOG_TRACE, amountStr.c_str());
	
		GM->gameGrid.MovePlayer(true, rollAmount);
	}
	else if (IsKeyPressed(KEY_Q))
	{
		int rollAmount = GetRandomValue(0, 2);
		auto amountStr = "Player Move -- Roll Amount: " + std::to_string(rollAmount);
		TraceLog(LOG_TRACE, amountStr.c_str());

		GM->gameGrid.MovePlayer(false, rollAmount);
	}
}

bool PlayerTurnPhase::Uninitialize()
{
	return true;
}

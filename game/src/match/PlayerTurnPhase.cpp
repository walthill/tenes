#include "raylib.h"
#include "PlayerTurnPhase.h"
#include "Game.h"

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
	if (IsKeyPressed(KEY_SPACE))
	{
		TraceLog(LOG_TRACE, "SPACEBAR");
		//GM->SetNextPhase();
	}
}

bool PlayerTurnPhase::Uninitialize()
{
	return true;
}

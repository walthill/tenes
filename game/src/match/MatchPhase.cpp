#include "raylib.h"
#include "MatchPhase.h"

MatchPhase::MatchPhase()
{
}

bool MatchPhase::Initialize()
{
	auto str = "MATCH::Initializing " + GetName();
	TraceLog(LOG_TRACE, str.c_str());

	return true;
}

void MatchPhase::Start()
{
}

void MatchPhase::Update()
{
}

void MatchPhase::Render()
{
}

bool MatchPhase::Uninitialize()
{
	auto str = "Uninitializing " + GetName();
	TraceLog(LOG_TRACE, str.c_str());

	return true;
}

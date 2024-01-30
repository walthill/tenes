#include "raylib.h"
#include "MatchPhase.h"

MatchPhase::MatchPhase()
{
}

bool MatchPhase::Initialize()
{
#if DEBUG
	auto str = "MATCH::Initializing " + GetName();
	TraceLog(LOG_TRACE, str.c_str());
#endif

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
#if DEBUG
	auto str = "Uninitializing " + GetName();
	TraceLog(LOG_TRACE, str.c_str());
#endif
	return true;
}

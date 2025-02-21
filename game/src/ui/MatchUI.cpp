#include "MatchUI.h"
#include "raylib.h"
#include <string>

MatchUI::MatchUI()
{
	m_playerScore = 0;
	m_playerPieceCount = 1;
	m_cpuScore = 0;
	m_cpuPieceCount = 1;
}

void MatchUI::Render()
{
	DrawText(c_playerHeader, 50, 25, 32, BLACK);
	DrawText(c_cpuHeader, GetScreenWidth() - 100, 25, 32, BLACK);
	
	//player pieces
	if (m_playerPieceCount == 1) {
		DrawRectangle(60, 25 * 2.5f, 16, 16, BLACK);
		DrawRectangleLines(70 + 16, 25 * 2.5f, 16, 16, BLACK);
	}
	else if (m_playerPieceCount == 2) {
		DrawRectangle(60, 25 * 2.5f, 16, 16, BLACK);
		DrawRectangle(70 + 16, 25 * 2.5f, 16, 16, BLACK);
	}

	//cpu pieces
	if (m_cpuPieceCount == 1) {
		DrawRectangle(GetScreenWidth() - 90, 25 * 2.5f, 16, 16, BLACK);
		DrawRectangleLines(GetScreenWidth() - 80 + 16, 25 * 2.5f, 16, 16, BLACK);
	}
	else if (m_cpuPieceCount == 2)
	{
		DrawRectangle(GetScreenWidth() - 90, 25 * 2.5f, 16, 16, BLACK);
		DrawRectangle(GetScreenWidth() - 80 + 16, 25 * 2.5f, 16, 16, BLACK);
	}

	DrawText(std::to_string(m_playerScore).c_str(), 50, 25 * 3.5f, 32, BLACK);
	DrawText(std::to_string(m_cpuScore).c_str(), GetScreenWidth() - 100, 25 * 3.5f, 32, BLACK);
}

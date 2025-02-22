#ifndef MATCH_UI_H
#define MATCH_UI_H

class MatchUI
{
	public:
		MatchUI();
		~MatchUI() {};

		void Render();

		void IncrementTurnCount() { m_turnCount++; }
		void RefreshPieceUI(bool a_isPlayer) { a_isPlayer ? m_playerPieceCount++ : m_cpuPieceCount++; }
		void UpdateScores(int a_playerScore, int a_cpuScore) { m_playerScore = a_playerScore; m_cpuScore = a_cpuScore; }

private:
		int m_playerScore;
		int m_cpuScore;
		int m_playerPieceCount;
		int m_cpuPieceCount;
		int m_turnCount;

		const char* c_turnHeader = "TURN ";
		const char* c_playerHeader = "YOU";
		const char* c_cpuHeader = "CPU";
};

#endif // !MATCH_UI_H
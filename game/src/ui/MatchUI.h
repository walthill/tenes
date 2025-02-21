#ifndef MATCH_UI_H
#define MATCH_UI_H

class MatchUI
{
	public:
		MatchUI();
		~MatchUI();

		void Update();
		void Render();

	private:
		int m_playerScore;
		int m_cpuScore;
		int m_playerPieceCount;
		int m_cpuPieceCount;

		const char* c_playerHeader = "YOU";
		const char* c_cpuHeader = "CPU";
};

#endif // !MATCH_UI_H
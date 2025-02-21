#ifndef PIECE_H
#define PIECE_H

#include "raymath.h"

class Piece
{
	public:
		Piece();
		Piece(int a_lives, bool a_isPlayer, int a_boardIndex);

		void Update();
		void Render();

		inline int GetBoardIndex() { return m_boardIndex; }
		void SetBoardIndex(int a_index);

		void SetPosition(Vector2 a_pos) { m_position = a_pos; };

	private:
		int m_boardIndex;
		bool m_isPlayer;
		Vector2 m_position;

};

#endif // !PIECE_H

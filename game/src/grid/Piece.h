#ifndef PIECE_H
#define PIECE_H

#include "raymath.h"

class Piece
{
	public:
		Piece();
		Piece(bool a_isPlayer, int a_boardIndex);

		void Update();
		void Render();

		inline int GetBoardIndex() const { return m_boardIndex; }
		inline bool HasScored() const { return m_scored; }
		inline bool IsVisible() const { return m_visible; }

		void SetBoardIndex(int a_index);
		void SetPosition(Vector2 a_pos) { m_position = a_pos; };
		void SetVisible(bool a_visible) { m_visible = a_visible; }

		static const int PieceSize = 64;

	private:
		int m_boardIndex;
		bool m_isPlayer;
		bool m_scored;
		bool m_visible;
		Vector2 m_position;

};

#endif // !PIECE_H

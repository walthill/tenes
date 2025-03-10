#ifndef PIECE_H
#define PIECE_H

#include "raymath.h"
#include <vector>

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
		inline bool IsMoving() const { return m_isMoving; }
		inline Vector2 GetPosition() const { return m_position; }

		void SetBoardIndex(int a_index);
		void SetPosition(Vector2 a_pos) { m_position = a_pos; };
		void SetVisible(bool a_visible) { m_visible = a_visible; }

		void StartMovement(int a_index, const std::vector<Vector2>& a_path);
		bool Move();

		static const int PieceSize = 64;

	private:
		int m_boardIndex;
		bool m_isPlayer;
		bool m_scored;
		bool m_visible;
		Vector2 m_position;
		// Movement state variables
		bool m_isMoving = false;
		Vector2 m_startPos;
		Vector2 m_endPos;
		std::vector<Vector2> m_path;
		int m_currentPathIndex;
		float m_elapsedTime = 0.0f;
		float m_duration = 0.35f;
};

#endif // !PIECE_H

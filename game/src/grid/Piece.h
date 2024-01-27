#ifndef PIECE_H
#define PIECE_H

class Piece
{
	public:
		Piece();
		Piece(int a_lives, bool a_isPlayer, int a_boardIndex);

		inline int GetBoardIndex() { return m_boardIndex; }
		void SetBoardIndex(int a_index);

	private:
		int m_boardIndex;
		bool m_isPlayer;
		int m_lives;		//might not actually be lives..tbd

};

#endif // !PIECE_H

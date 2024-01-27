#ifndef PIECE_H
#define PIECE_H

class Piece
{
	public:
		Piece();
		Piece(int a_lives, bool a_isPlayer);

	private:
		bool m_isPlayer;
		int m_lives;		//might not actually be lives..tbd

};

#endif // !PIECE_H

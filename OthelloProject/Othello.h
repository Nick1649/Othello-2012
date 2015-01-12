#ifndef _OTHELLO_
#define _OTHELLO_

enum boardPieces {Blank, White, Black};
const int BOARD_SIZE = 8;

class Othello
{
	private:
		boardPieces theBoard[BOARD_SIZE][BOARD_SIZE];
		boardPieces tempBoard[BOARD_SIZE][BOARD_SIZE];
		boardPieces currentPlayer;
		boardPieces otherPlayer;
		void Init ();
		void Draw ();
		bool ValidMove (int, int);
		bool AnyValidMoves ();
		void MakeMove (int, int);
		void GetMove (int&, int&);
		bool Boundries (int, int);
		void NoMoves ();
		void Undo ();
	public:
		Othello ();
		void Play ();
};

#endif
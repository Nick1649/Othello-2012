#include <iostream>
#include <iomanip>
#include <string>

#include "Othello.h"

using namespace std;

Othello :: Othello()
{
	for(int row = 0; row < BOARD_SIZE; row++)
	{
		for(int col = 0; col < BOARD_SIZE; col++)
		{
			theBoard[row][col] = Blank;
		}
	}
}

void Othello ::Play()
{

	int row;
	int col;
	int totBlack;
	int totWhite;

	Othello();
	Init();
	Draw();
	GetMove(row, col);
	
	while (true)
	{
		for(int row = 0; row < BOARD_SIZE; row++)
		{
			for(int col = 0; col < BOARD_SIZE; col++)
			{
				tempBoard[row][col] = theBoard[row][col];
			}
		}

		if (!AnyValidMoves())
		{
			NoMoves();

			if (!AnyValidMoves())
			{
				break;
			}
		}
		
		if (ValidMove(row, col))
		{
			MakeMove(row, col);
			Undo();
			system ("cls");
			Draw();
			GetMove(row, col);
		}
		else
		{
			system ("cls");
			Draw();
			cout << "Invalid Move, please try again." << endl;
			GetMove(row, col);
		}
	}
	for(int row = 0; row < BOARD_SIZE; row++)
	{
		for(int col = 0; col < BOARD_SIZE; col++)
		{
			if (theBoard[row][col] == Black)
			{
				totBlack++;
			}
			else if (theBoard[row][col] == White)
			{
				totWhite++;
			}
		}
	}
	cout << "Black scored: " << totBlack << endl;
	cout << "White scored: " << totWhite << endl;
	if (totBlack > totWhite)
	{
		cout << "Black wins!" << endl;
	}
	else if (totWhite > totBlack)
	{
		cout << "White wins!" << endl;
	}
	else
	{
		cout << "Tie!" << endl;
	}
}

void Othello :: Init()
{
	theBoard[3][3] = White;
	theBoard[3][4] = Black;
	theBoard[4][3] = Black;
	theBoard[4][4] = White;
	currentPlayer = Black;
	otherPlayer = White;
}

void Othello :: Draw()
{
	for(int col = 0; col < BOARD_SIZE; col++)				//Determines wether or not to display the number at the top of the columns.
	{		
			cout << ' ' << col + 1;
	}
	cout << endl;
	for(int row = 0; row < BOARD_SIZE; row++)				//The rest of this function just draws the entire board.
	{
		for(int col = 0; col < BOARD_SIZE; col++)
		{
			cout << "+-";
		}

			cout << '+';
			cout << endl;

		for(int col = 0; col < BOARD_SIZE; col++)			//This specific for loop fills the board with values from the array.
		{
			cout << '|';
			if(theBoard[row][col] == Black)
			{
				cout << 'X';
			}
			if(theBoard[row][col] == White)
			{
				cout << 'O';
			}
			if(theBoard[row][col] == Blank)
			{
				cout << ' ';
			}
		}
		cout << '|' << row + 1 << endl;
	}
	for(int col = 0; col < BOARD_SIZE; col++)
	{
		cout << "+-";
	}
	cout << '+' << endl;
}

bool Othello :: ValidMove(int row, int col)
{
	int i;
	int j;
	int r;
	int c;

	if (theBoard[row][col] == Blank  && !Boundries(row, col))
	{
	
		for (i = -1; i < 2; i++)
		{
			for (j = -1; j < 2; j++)
			{
				r = row + i;
				c = col + j;

				if (!Boundries(r, c) && theBoard[r][c] == otherPlayer)
				{
					do
					{
						r += i;
						c += j; 
					}
					while(!Boundries(r, c) && theBoard[r][c] == otherPlayer);

					if (theBoard[r][c] == currentPlayer)
					{
						return (true);
					}
				}
			}
		}
	}

	return (false);
}

bool Othello :: AnyValidMoves()
{
	for(int row = 0; row < BOARD_SIZE; row++)
	{
		for(int col = 0; col < BOARD_SIZE; col++)
		{
			if(ValidMove(row, col))
				return true;
		}
	}
	return false;
}

void Othello :: MakeMove(int row, int col)
{
	int i;
	int j;
	int r;
	int c;

	theBoard[row][col] = currentPlayer; 

	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			r = row + i;
			c = col + j;

			if (!Boundries(r, c) && theBoard[r][c] == otherPlayer)
			{
				do
				{
					r += i;
					c += j; 
				}
				while(!Boundries(r, c) && theBoard[r][c] == otherPlayer);

				if (theBoard[r][c] == currentPlayer)
				{
					do
					{
						r -= i;
						c -= j; 

						theBoard[r][c] = currentPlayer;
					}
					while(r != row || c != col);	
				}
			}
		}
	}
	
	if ( currentPlayer == Black)
	{
		currentPlayer = White;
		otherPlayer = Black;
	}
	else
	{
		currentPlayer = Black;
		otherPlayer = White;
	}
}

void Othello :: GetMove(int &row, int &col)
{
	switch (currentPlayer)
	{
	case 2 : cout << "Player 1 where would you like to place your token (X)" << endl;
		break;
	case 1 : cout << "Player 2 where would you like to place your token (O)" << endl;
		break;
	}

	cout << "Row: ";
	cin  >> row;

	row -= 1;

	cout << "Column: ";
	cin  >> col;

	col -= 1;
}

bool Othello :: Boundries(int row, int col)
{
	if (row > BOARD_SIZE || row < 0)
	{
		return (true);
	}
	else if (col > BOARD_SIZE || col < 0)
	{
		return (true);
	}
		
	return (false);
}

void Othello :: NoMoves()
{
	if (currentPlayer == Black)
	{
		currentPlayer = White;
	}
	else if (currentPlayer == White)
	{
		currentPlayer = Black;
	}

}

void Othello :: Undo()
{
	char undo;
	do
	{
	cout << "Do you want to undo? Enter Y/N: ";
	cin  >> undo;
	undo = toupper(undo);
	}
	while(undo != 'Y' && undo != 'N');

	if(undo == 'Y')
	{
		for(int row = 0; row < BOARD_SIZE; row++)
		{
			for(int col = 0; col < BOARD_SIZE; col++)
			{
				theBoard[row][col] = tempBoard[row][col];
			}
		}

		if ( currentPlayer == Black)
		{
			currentPlayer = White;
			otherPlayer = Black;
		}
		else
		{
			currentPlayer = Black;
			otherPlayer = White;
		}
	}
}
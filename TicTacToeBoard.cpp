#include "TicTacToeBoard.h"
/**
 * Class for representing a 3x3 Tic-Tac-Toe game board, using the Piece enum
 * to represent the spaces on the board.
**/

//Switches turn member variable to represent whether it's X's or O's turn
void TicTacToeBoard::toggleTurn()
{
	if( turn == X )
		turn = O;
	else
		turn = X;
}

//Constructor sets an empty board and specifies it is X's turn first
TicTacToeBoard::TicTacToeBoard()
{
	turn = X;
	clearBoard();
}

//Resets each board location to the Blank Piece value
void TicTacToeBoard::clearBoard()
{
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			board[i][j] = Blank;
}

/**
 * Places the piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. placePiece does 
 * NOT allow to place a piece in a location where there is already a piece.
 * In that case, placePiece just returns what is already at that location. 
 * Out of bounds coordinates return the Piece Invalid value
**/ 
Piece TicTacToeBoard::placePiece(int row, int column)
{
	Piece at = Invalid;
	if( row >= 0 && row < BOARDSIZE && column >= 0 && column < BOARDSIZE)
	{
		if(board[row][column] == Blank)
		{
			board[row][column] = turn;
		}
		at = board[row][column];
	}
	toggleTurn();
  	return at;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece TicTacToeBoard::getPiece(int row, int column)
{
	if( row >= 0 && row < BOARDSIZE && column >= 0 && column < BOARDSIZE)
	{
		return board[row][column];
	}
	else
	{
  		return Invalid;
	}
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won.
**/
Piece TicTacToeBoard::getWinner()
{
	bool allBlank = true;
	for(int place=0; place<BOARDSIZE; place++)
	{
		if( board[place][0] == board[place][1] 
			 && board[place][0] == board[place][2] 
			 && board[place][0] != Blank )
			return board[place][0];
		else if(board[0][place] == board[1][place] 
			 	&& board[0][place] == board[2][place] 
			 	&& board[0][place] != Blank )
			return board[0][place];

		//No winner found so far, so check if any cells in row are blank
		if( board[place][0] == Blank || board[place][1] == Blank 
			|| board[place][2]==Blank)
			allBlank = false;
	}
	if( board[0][0] == board[1][1] && board[0][0] == board[2][2] 
		&& board[1][1] != Blank )
	{
		return board[1][1];
	}
	else if( board[2][0] == board[1][1] && board[2][0] == board[0][2]
			 && board[1][1] != Blank )
	{
		return board[1][1];
	}
	else if( board[1][0] == board[1][1] && board[1][0] == board[1][2] 
			 && board[1][0] != Blank )
		return board[1][0];
	else if( allBlank )
		return Blank;
	else
  		return Invalid;
}

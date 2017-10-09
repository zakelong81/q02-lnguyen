#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  board.resize(BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  for (int row = 0; row < BOARD_ROWS; row++)
      for (int column = 0; column < BOARD_COLS;column++)
          board[row][column] = Blank;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  if (turn==X)
    return turn=O;
  if (turn==O)
    return turn=X;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  if(row > BOARD_ROWS-1  || column > BOARD_COLS-1 || column < 0 || row < 0)
        return Invalid;
  return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  int countX = 0; int countO = 0;int aX = 0; int aO = 0;
  int row =0;  int column = 0;
  bool checkwinner=true;

  while(row<BOARD_ROWS)
  {
      while(column<BOARD_COLS)
      {
        if(board[row][column]==Blank)
            checkwinner=false;
        column++;
      }
      row++;
  }

  if(checkwinner==false)
      return Invalid;

  row=0; column=0;
  while(row<BOARD_ROWS)
  {
      while(column<BOARD_COLS)
      {
        if(board[row][column]==aO)
        {
          countO++;
          if(countO>aO)
              aO = countO;
          countX = 0;
        }
        else
        {
          countX++;
          if(countX > aX)
              aX = countX;
          countO = 0;
        }
        column++;
      }
      countX = 0;
      countO = 0;
      row++;
  }

  countX = 0; countO = 0;
  row=0; column=0;
  while(column<BOARD_COLS)
  {
      while(row<BOARD_ROWS)
      {
        if(board[row][column]==aO)
        {
          countO++;
          if(countO>aO)
              aO = countO;
          countX = 0;
        }
        else
        {
          countX++;
          if(countX>aX)
              aX = countX;
          countO = 0;
        }
        row++;
      }
      countX = 0;
      countO = 0;
      column++;
  }
  if(aX>aO)             return aX;
  else if(aO > aX)      return aO;
  else                return Blank;
  return Blank;
}

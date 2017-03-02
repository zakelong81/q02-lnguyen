/**
 * Unit Tests for TicTacToeBoard
**/
#include <string>
#include <gtest/gtest.h>
#include "TicTacToeBoard.h"
 
std::string hint;

class TicTacToeBoardTest : public ::testing::Test
{
	protected:
		TicTacToeBoardTest(){} //constructor runs before each test
		virtual ~TicTacToeBoardTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};
/*
TEST(TicTacToeBoardTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
*/

//Constructor sets an empty board and specifies it is X's turn first
//  	TicTacToeBoard();

TEST(TicTacToeBoardTest, testConstructor)
{
	hint = "Is the constructor making the board the right size?";
	TicTacToeBoard board;

	ASSERT_EQ( Blank, board.getPiece(0,0) ) <<hint;
	ASSERT_EQ( Blank, board.getPiece(0,2) ) <<hint;
	ASSERT_EQ( Blank, board.getPiece(2,2) ) <<hint;
	ASSERT_EQ( Invalid, board.getPiece(3,0)) <<hint;
	ASSERT_EQ( Invalid, board.getPiece(0,3)) <<hint;
}

//Resets each board location to the Blank Piece value
//void clearBoard();

TEST(TicTacToeBoardTest, testClearClearedBoard)
{
	hint = "Can we effectively clear the board at any time?";
	TicTacToeBoard board;

	board.clearBoard();
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			ASSERT_EQ( Blank, board.getPiece(i,j) ) <<hint;
}

TEST(TicTacToeBoardTest, testClearFullBoard)
{
	hint = "Can the clear board remove pieces at any position?";
	TicTacToeBoard board;
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			board.placePiece(i,j);

	board.clearBoard();
	for(int i=0; i<BOARDSIZE; i++)
		for(int j=0; j<BOARDSIZE; j++)
			ASSERT_EQ( Blank, board.getPiece(i,j) ) <<hint;
}

/**
 * Places the piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. placePiece does 
 * NOT allow to place a piece in a location where there is already a piece.
 * In that case, placePiece just returns what is already at that location. 
 * Out of bounds coordinates return the Piece Invalid value
**/ 
//Piece placePiece(int row, int column);

TEST(TicTacToeBoardTest, testPlacePieceLowerBounds)
{
	hint = "Can pieces be placed properly at the edges of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(X, board.placePiece(0,0) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceUpperBounds)
{
	hint = "Can pieces be placed properly at the edges of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(X, board.placePiece(2,2) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceUnderBounds)
{
	hint = "What should happen when pieces are place outside of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.placePiece(-1,-1) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceUnderBoundsRow)
{
	hint = "What should happen when pieces are place outside of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.placePiece(-1,0) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceUnderBoundsCol)
{
	hint = "What should happen when pieces are place outside of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.placePiece(1,-1) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceOverBounds)
{
	hint = "What should happen when pieces are place outside of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.placePiece(3,3) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceOverBoundsRow)
{
	hint = "What should happen when pieces are place outside of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.placePiece(3,0) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceOverBoundsCol)
{
	hint = "What should happen when pieces are place outside of the board?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.placePiece(1,3) ) <<hint;
}

TEST(TicTacToeBoardTest, testPlacePieceOverPieceDiff)
{
	hint = "What should happen when pieces are placed ontop of another?";
	TicTacToeBoard board;

	board.placePiece(1,1); //places X
	ASSERT_EQ(X, board.placePiece(1,1) ) <<hint; //fails to place O
}

TEST(TicTacToeBoardTest, testPlacePieceOverPieceSafeX)
{
	hint = "What should happen when pieces are placed ontop of another?";
	TicTacToeBoard board;

	board.placePiece(1,1); //places X
	board.placePiece(1,1); //fails to place O
	ASSERT_EQ(X, board.placePiece(1,1) ) <<hint; //fails to place X
}

TEST(TicTacToeBoardTest, testPlacePieceOverPieceSafeO)
{
	hint = "What should happen when pieces are placed ontop of another?";
	TicTacToeBoard board;

	board.placePiece(0,0); //places X
	board.placePiece(2,1); //places O
	board.placePiece(2,1); //fails to place X
	ASSERT_EQ(O, board.placePiece(2,1) ) <<hint;
}
/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
//Piece getPiece(int row, int column);

TEST(TicTacToeBoardTest, testGetPieceValid)
{
	hint = "What should happen when checking existing piece placement?";
	TicTacToeBoard board;

	board.placePiece(2,1);
	ASSERT_EQ(X, board.getPiece(2,1) ) <<hint;
}

TEST(TicTacToeBoardTest, testGetPieceValidTwice)
{
	hint = "What should happen when checking existing piece placement?";
	TicTacToeBoard board;

	board.placePiece(0,1);
	ASSERT_EQ(X, board.getPiece(0,1) ) <<hint;
	ASSERT_EQ(X, board.getPiece(0,1) ) <<hint;
}

TEST(TicTacToeBoardTest, testGetPieceValidAfterTwoPlace)
{
	hint = "What should happen when checking existing piece placement?";
	TicTacToeBoard board;

	board.placePiece(0,1);
	board.placePiece(0,2);
	board.placePiece(0,2);
	ASSERT_EQ(O, board.getPiece(0,2) ) <<hint;
}

TEST(TicTacToeBoardTest, testGetPieceEmpty)
{
	hint = "What should happen when checking location without a piece?";
	TicTacToeBoard board;

	ASSERT_EQ(Blank, board.getPiece(1,1) ) <<hint;
}

TEST(TicTacToeBoardTest, testGetPieceOverBoundsRow)
{
	hint = "What should happen when checking pieces at invalid locations?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.getPiece(3,1) ) <<hint;
}

TEST(TicTacToeBoardTest, testGetPieceOverBoundsCol)
{
	hint = "What should happen when checking pieces at invalid locations?";
	TicTacToeBoard board;

	ASSERT_EQ(Invalid, board.getPiece(0,3) ) <<hint;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won.
**/
//Piece getWinner();

TEST(TicTacToeBoardTest, testWinnerEmpty)
{
	hint = "Who has won when the game first starts?";
	TicTacToeBoard board;
	ASSERT_EQ(Invalid, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerIncomplete)
{
	hint = "Who has won when still mid-game?";
	TicTacToeBoard board;
	board.placePiece(0,0);
	board.placePiece(2,2);
	ASSERT_EQ(Invalid, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerRepeatedly)
{
	hint = "What happens if checking who won after each move?";
	TicTacToeBoard board;
	ASSERT_EQ(Invalid, board.getWinner() );
	board.placePiece(0,0);
	ASSERT_EQ(Invalid, board.getWinner() );
	board.placePiece(1,1);
	ASSERT_EQ(Invalid, board.getWinner() );
	board.placePiece(2,2);
	ASSERT_EQ(Invalid, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerFullTie)
{
	hint = "What happens if checking who won after a tie?";
	TicTacToeBoard board;
	// X X O
	// O O X
	// X O X
	board.placePiece(0,0); //X
	board.placePiece(0,2); //O
	board.placePiece(0,1); //X
	board.placePiece(1,0); //O
	board.placePiece(1,2); //X
	board.placePiece(1,1); //O
	board.placePiece(2,0); //X
	board.placePiece(2,1); //O
	board.placePiece(2,2); //X
	ASSERT_EQ(Blank, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerInvalidTie)
{
	hint = "What happens if checking who won after invalid placements?";
	TicTacToeBoard board;

	board.placePiece(0,0);
	board.placePiece(0,-1);
	board.placePiece(0,-1);
	board.placePiece(1,-1);
	board.placePiece(1,-1);
	board.placePiece(1,-1);
	board.placePiece(2,-1);
	board.placePiece(2,-1);
	board.placePiece(2,-1);
	ASSERT_EQ(Invalid, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerVerticalX)
{
	hint = "Can X win in any direction?";
	TicTacToeBoard board;
	// X O 
	// X O
	// X
	board.placePiece(0,0);
	board.placePiece(0,1);
	board.placePiece(1,0);
	board.placePiece(1,1);
	board.placePiece(2,0);
	ASSERT_EQ(X, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerHorizontalX)
{
	hint = "Can X win in any direction?";
	TicTacToeBoard board;
	//   O 
	//   O
	// X X X
	board.placePiece(2,0);
	board.placePiece(0,1);
	board.placePiece(2,1);
	board.placePiece(1,1);
	board.placePiece(2,2);
	ASSERT_EQ(X, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerDiagonalX)
{
	hint = "Can X win in any direction?";
	TicTacToeBoard board;
	// X O 
	//   X
	//   O X
	board.placePiece(0,0);
	board.placePiece(0,1);
	board.placePiece(1,1);
	board.placePiece(2,1);
	board.placePiece(2,2);
	ASSERT_EQ(X, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerVerticalO)
{
	hint = "Can O win in any direction?";
	TicTacToeBoard board;
	//   O X
	// X O
	// X O
	board.placePiece(2,0);
	board.placePiece(0,1);
	board.placePiece(1,0);
	board.placePiece(1,1);
	board.placePiece(2,0);
	board.placePiece(2,1);
	ASSERT_EQ(O, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerHorizontalO)
{
	hint = "Can O win in any direction?";
	TicTacToeBoard board;
	//   X 
	// O O O
	// X   X
	board.placePiece(0,1);
	board.placePiece(1,0);
	board.placePiece(2,0);
	board.placePiece(1,1);
	board.placePiece(2,2);
	board.placePiece(1,2);
	ASSERT_EQ(O, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerDiagonalO)
{
	hint = "Can O win in any direction?";
	TicTacToeBoard board;
	// X   O
	//   O 
	// O X X
	board.placePiece(0,0);
	board.placePiece(0,2);
	board.placePiece(2,2);
	board.placePiece(1,1);
	board.placePiece(2,1);
	board.placePiece(2,0);
	ASSERT_EQ(O, board.getWinner() ) <<hint;
}

TEST(TicTacToeBoardTest, testWinnerFullX)
{
	hint = "Can X win on the last move?";
	TicTacToeBoard board;
	// X X X
	// O O X
	// O X O
	board.placePiece(0,0); //X
	board.placePiece(1,0); //O
	board.placePiece(0,1); //X
	board.placePiece(1,1); //O
	board.placePiece(1,2); //X
	board.placePiece(2,0); //O
	board.placePiece(1,1); //X
	board.placePiece(2,2); //O
	board.placePiece(0,2); //X
	ASSERT_EQ(X, board.getWinner() ) <<hint;
}


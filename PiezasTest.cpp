/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, structorCheck)
{
  bool check = 1;
  Piezas piezas;
  for(int i=0;i<BOARD_ROWS;i++)
  {
    for(int j=0;j<BOARD_COLS;j++)
    {
      if(piezas.pieceAt(i,j)!=Blank)
          check = 0;
    }
  }
  ASSERT_EQ(1,check);
}

TEST(PiezasTest, winnerCheckX)
{
  Piezas piezas;
  piezas.reset();
  piezas.dropPiece(0);
  piezas.dropPiece(1);
  piezas.dropPiece(2);
  piezas.dropPiece(3);
  piezas.dropPiece(2);
  piezas.dropPiece(0);
  piezas.dropPiece(2);
  piezas.dropPiece(3);
  piezas.dropPiece(1);
  piezas.dropPiece(0);
  piezas.dropPiece(3);
  piezas.dropPiece(1);

  ASSERT_EQ(true, piezas.gameState()== X);
}

TEST(PiezasTest, winnerCheckOfalse)
{
  Piezas piezas;

  piezas.reset();
  piezas.dropPiece(0);
  piezas.dropPiece(1);
  piezas.dropPiece(2);
  piezas.dropPiece(3);
  piezas.dropPiece(3);
  piezas.dropPiece(2);
  piezas.dropPiece(2);
  piezas.dropPiece(0);
  piezas.dropPiece(0);
  piezas.dropPiece(1);
  piezas.dropPiece(3);
  piezas.dropPiece(1);

  ASSERT_EQ(false, piezas.gameState()== O);
}

TEST(PiezasTest, winnerCheckTIEfalse)
{
  Piezas piezas;

  piezas.reset();
  piezas.dropPiece(1);
  piezas.dropPiece(0);
  piezas.dropPiece(2);
  piezas.dropPiece(2);
  piezas.dropPiece(3);
  piezas.dropPiece(3);
  piezas.dropPiece(0);
  piezas.dropPiece(1);
  piezas.dropPiece(2);
  piezas.dropPiece(3);
  piezas.dropPiece(0);
  piezas.dropPiece(1);


  ASSERT_EQ(false, piezas.gameState()== Blank);
}

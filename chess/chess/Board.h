#ifndef BOARD_H
#define BOARD_H

#include "Square.h"
#define MINC 1;
#define MINR 1;
#define MAXC 8;
#define MAXR 8;
class Board
{
	private:
		Square m_squares[10][10];
	public:
		const int MIN_COL_INDEX = MINC;
		const int MIN_ROW_INDEX = MINR;
		const int MAX_COL_INDEX = MAXC;
		const int MAX_ROW_INDEX = MAXR;
		Board();
		//~Board();
		Board(const Board& board);
		Square* getSquare(int row, int col);
		
};

#endif
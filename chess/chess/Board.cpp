#include "Board.h"

Board::Board()
{
}

Board::Board(const Board& board)
{
	for(int row=0; row<10; row++)
	{
		for(int col=0; col<10; col++)
		{
			this->m_squares[row][col] = board.m_squares[row][col];
		}
	}
}

Square* Board::getSquare(int row, int col)
{
	return &m_squares[row][col];
}

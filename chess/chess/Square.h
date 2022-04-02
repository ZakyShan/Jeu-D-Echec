#ifndef SQUARE_H
#define SQUARE_H

#include "Piece.h"

class Square
{
	
	public:
		Square();
		Square(const Square& square);
		bool occupiedState();
		bool occupySquare(Piece* piece);
		Piece* removeOccupyingPiece();
		Piece* getOccupyingPiece();
	private:
		Piece* m_occupyingPiece;
};

#endif
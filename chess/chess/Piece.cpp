
#include "Header.h"
#include <iostream>

Piece::Piece(int x, int y, bool white){
	this->pos = Position(x, y);
	this->white = white;
}

Piece::Piece(Position pos, bool white)
{
	this->pos = pos;
	this->white = white;
}

bool Piece::isdntMove()
{
	return false;
}

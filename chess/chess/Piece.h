//#pragma once
#include <iostream>
#include "Position.h"


class Piece {

public:
	Piece() = default;
	Piece(int x, int y, bool white);
	Piece(Position pos, bool white);

private:

	bool isdntMove();


	Position pos;
	bool white;
	bool move;

};


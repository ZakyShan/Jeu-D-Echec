#if !defined Tour_h
#define Tour_h
#include "Piece.h"


class Tour : virtual public Piece
{
public:
	Tour(bool white, bool left);
	bool mouvementValide(Echiquier& e, int x, int y);
	char codePiece();
};

#endif Tour_h
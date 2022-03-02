
#if !defined Cavalier_h
#define Cavalier_h
#include "Piece.h"

class Cavalier : virtual public Piece
{
public:
	Cavalier(bool white, bool left);
	bool mouvementValide(Echiquier& e, int x, int y);
	char codePiece();
};
#endif Cavalier_h
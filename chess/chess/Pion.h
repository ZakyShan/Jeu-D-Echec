#if !defined Pion_h
#define Pion_h
#include "Piece.h"
class Pion : virtual public Piece
{
public:
	Pion(int x, bool white);
	bool mouvementValide(Echiquier& e, int x, int y);
	char codePiece();
};
#endif Pion_h
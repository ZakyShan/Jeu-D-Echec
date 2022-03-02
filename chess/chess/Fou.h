#if !defined Fou_h
#define Fou_h
#include "Piece.h"
class Fou : virtual public Piece
{
public:
	Fou(bool white, bool left);
	bool mouvementValide(Echiquier& e, int x, int y);
	char codePiece();
};
#endif Fou_h
#if !defined Reine_h
#define Reine_h
#include "Fou.h"
#include "Tour.h"
class Reine : public Fou, public Tour
{
public:
	Reine(bool white);
	bool mouvementValide(Echiquier& e, int x, int y);
	char codePiece();
};
#endif Reine_h
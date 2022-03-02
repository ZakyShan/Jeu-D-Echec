#include <iostream>
#include "Fou.h"
#include "Tour.h"
#include "Echiquier.h"
#include "Reine.h"
using namespace std;
Reine::Reine(bool white) : Piece(4, white ? 1 : 8, white), Fou(white, true), Tour(white, true)
{

    cout << "Constructeur Reine" << endl;
}

bool
Reine::mouvementValide(Echiquier& e, int x, int y)
{
    bool mouvementOk = false;

    if (Tour::mouvementValide(e, x, y) || Fou::mouvementValide(e, x, y))
    {
        cout << "\nLe mouvement de la Reine est valide." << endl;
        mouvementOk = true;
    }

    return (mouvementOk);
}

char
Reine::codePiece()
{
    return (m_white) ? 'Q' : 'q';
}

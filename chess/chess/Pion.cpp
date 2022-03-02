#include <iostream>
#include "Pion.h"
#include "Echiquier.h"
using namespace std;

Pion::Pion(int x, bool white) : Piece(x, white ? 2 : 7, white)
{
    cout << "Constructeur Pion" << endl;
}

bool
Pion::mouvementValide(Echiquier& e, int x, int y)
{
    bool estValide = false;

    if ((m_y == 2 && m_white) || (m_y == 7 && !m_white))
    {
        //Le pion peut avancer de 1 ou 2 cases ou en diagonale si piece adverse
        if ((x == m_x && y == m_y + 2 && m_white) || (x == m_x && y == m_y - 2 && !m_white)) //cas avancer de 2 cases
        {
            if (m_white && e.getPiece(m_x, m_y + 1) == NULL && e.getPiece(m_x, m_y + 2) == NULL)
            {
                cout << "Le mouvement du Pion est valide." << endl;
                estValide = true;
            }
            else
            {
                if (!m_white && e.getPiece(m_x, m_y - 1) == NULL && e.getPiece(m_x, m_y - 2) == NULL)
                {
                    cout << "Le mouvement du Pion est valide." << endl;
                    estValide = true;
                }
            }
        }
        else
        {
            if ((x == m_x && y == m_y + 1 && m_white) || (x == m_x && y == m_y - 1 && !m_white))    //Cas avancer 1 case
            {
                if (e.getPiece(x, y) == NULL)
                {
                    cout << "Le mouvement du Pion est valide." << endl;
                    estValide = true;
                }
            }
            else
            {
                if ((1 == abs(x - m_x) && y == m_y + 1 && m_white) || (1 == abs(x - m_x) && y == m_y - 1 && !m_white))
                {
                    if (e.getPiece(x, y) != NULL && e.getPiece(x, y)->isWhite() != m_white)
                    {
                        e.enleverPiece(x, y);
                        cout << "Le mouvement du Pion est valide." << endl;
                        estValide = true;
                    }
                }
            }
        }
    }
    else
    {
        if ((x == m_x && y == m_y + 1 && m_white) || (x == m_x && y == m_y - 1 && !m_white))
        {
            if (e.getPiece(x, y) == NULL)
            {
                cout << "Le mouvement du Pion est valide." << endl;
                estValide = true;
            }
        }
        else
        {
            if ((1 == abs(x - m_x) && y == m_y + 1 && m_white) || (1 == abs(x - m_x) && y == m_y - 1 && !m_white))
            {
                if (e.getPiece(x, y) != NULL && e.getPiece(x, y)->isWhite() != m_white)
                {
                    e.enleverPiece(x, y);
                    cout << "Le mouvement du Pion est valide." << endl;
                    estValide = true;
                }
            }
        }
    }

    return estValide;
}

char
Pion::codePiece()
{
    return (m_white) ? 'P' : 'p';
}

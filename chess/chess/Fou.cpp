#include <iostream>
#include "Fou.h"
#include "Echiquier.h"
using namespace std;
Fou::Fou(bool white, bool left) : Piece(left ? 3 : 6, white ? 1 : 8, white)
{
    cout << "Constructeur Fou" << endl;
}

bool
Fou::mouvementValide(Echiquier& e, int x, int y)
{
    int xDepart = this->x(); //Récupération du départ de la pièce
    int yDepart = this->y();
    bool estBlanche = this->isWhite();
    bool estValide = false;
    int ecartX = x - xDepart;
    int ecartY = y - yDepart;

    //vérifier si pièce sur chemin et vérifier si pièce sur case d'arrivée et sa couleur
    if (ecartX == ecartY || ecartX == -ecartY)   //pour aller en diagonale
    {
        if (ecartX > 0 && ecartY < 0)    //déplacement en haut à droite
        {
            while (xDepart != x && yDepart != y) //ET ou OU
            {
                yDepart++;
                yDepart--;

                if (e.getPiece(yDepart, yDepart) != NULL)
                {
                    if (xDepart == x && yDepart == y && e.getPiece(x, y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                    {
                        e.enleverPiece(x, y);
                        cout << "Le mouvement du Fou est valide : déplacement Haut Droite" << endl;
                        estValide = true;
                    }
                }
                else
                {
                    if (xDepart == x && yDepart == y && estValide == false)
                    {
                        cout << "Le mouvement du Fou est valide : déplacement Haut Droite" << endl;
                        estValide = true;
                    }
                }
            }
        }
        else
        {
            if (ecartX < 0 && ecartY > 0)    //déplacement en bas à gauche
            {
                while (xDepart != x && yDepart != y) //ET ou OU
                {
                    xDepart--;
                    yDepart++;

                    if (e.getPiece(yDepart, yDepart) != NULL)
                    {
                        if (xDepart == x && yDepart == y && e.getPiece(x, y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                        {
                            e.enleverPiece(x, y);
                            cout << "Le mouvement du Fou est valide : déplacement Bas Gauche" << endl;
                            estValide = true;
                        }
                    }
                    else
                    {
                        if (xDepart == x && yDepart == y && estValide == false)
                        {
                            cout << "Le mouvement du Fou est valide : déplacement Bas Gauche" << endl;
                            estValide = true;
                        }
                    }
                }
            }
            else
            {
                if (ecartX < 0 || ecartY < 0)    //déplacement haut gauche
                {
                    while (xDepart != x || yDepart != y) //ET ou OU
                    {
                        xDepart--;
                        yDepart--;

                        if (e.getPiece(xDepart, yDepart) != NULL)
                        {
                            if (xDepart == x && yDepart == y && e.getPiece(x, y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                            {
                                e.enleverPiece(x, y);
                                cout << "Le mouvement du Fou est valide : déplacement Haut Gauche" << endl;
                                estValide = true;
                            }
                        }
                        else
                        {
                            if (xDepart == x && yDepart == y && estValide == false)
                            {
                                cout << "Le mouvement du Fou est valide : déplacement Haut Gauche" << endl;
                                estValide = true;
                            }
                        }
                    }
                }
                else            //déplacement bas droite
                {
                    while (ecartX != x && ecartY != y) //ET ou OU
                    {
                        xDepart++;
                        yDepart++;

                        if (e.getPiece(xDepart, yDepart) != NULL)
                        {
                            if (xDepart == x && yDepart == y && e.getPiece(x, y)->isWhite() != estBlanche)   //Si pièce couleur joueur adverse alors on l'enlève !
                            {
                                e.enleverPiece(x, y);
                                cout << "Le mouvement du Fou est valide : déplacement Bas Droite" << endl;
                                estValide = true;
                            }
                        }
                        else
                        {
                            if (xDepart == x && yDepart == y && estValide == false)
                            {
                                cout << "Le mouvement du Fou est valide : déplacement Bas Droite" << endl;
                                estValide = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return estValide;
}

char
Fou::codePiece()
{
    return (m_white) ? 'F' : 'f';
}

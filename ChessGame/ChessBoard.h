#include <iostream>
#include "Pieces.h"



class Chessboard {
public:
	Chessboard();
	void initialisation();
	char chessboard[8][8][3];
	
};

void affiche(char chessboard[][8][3]);
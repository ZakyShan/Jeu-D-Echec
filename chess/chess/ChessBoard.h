#include <iostream>
#include "Pawn.h"



class Chessboard {
public:
	Chessboard();
	void initialisation();
	char chessboard[8][8][3];

};

void afficheWhite(char chessboard[8][8][3]);
void afficheBlack(char chessboard[8][8][3]);
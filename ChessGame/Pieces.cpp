#include <iostream>
#include "ChessBoard.h"



Pawn::Pawn(int x, int y, bool white){
	this->x = x;
	this->y = y;
	this->white = white;
	this->move = true;
}

Pawn Choix() {
	std::cout << "Quelle est la case de la pièce que vous souhaiter jouer" << std::endl;
	char *chr;
	std::cin >> *chr;
	if (chr.size()) {

	}
}

bool Pawn::goodMove(int &x, int &y, Pawn **chessboard[][8])
{
	if (**chessboard == 0) {
		if (isdntMove) {
			//if(x >)
		}
	}
	return false;
}
//return vrais si la piece n'a pas bougé retourne faux si la piece bouge
bool Pawn::isdntMove()
{
	if (move) {
		move = false;
		return true;
	}
	return move;
}




#include <iostream>
#include "ChessBoard.h"
#include <cctype>


Pawn::Pawn(int x, int y, bool white, const char name[3]) {
	this->x = x;
	this->y = y;
	this->white = white;
	this->move = true;
	for (int i = 0; i < 2; i++) {
		this->name[i] = name[i];
	}
}

Pawn Choix(char chessboard[][8][3], bool white) {
	std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
	char chr[2];
	std::cin >> chr;
	for (int i = 0; i < 2; i++) {
		//si la chaine est vide
		if (!chr[i]) {
			std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
			std::cin >> chr;
			i = 0;
		}

		//vérifie que le premier caractère est bien une lettre comprise entre a et h
		if (i == 0 && !((toupper(chr[i]) >= 'A' && (toupper(chr[i])) <= 'H'))) {
			std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
			std::cin >> chr;
			i = 0;
		}

		//vérifie que le deuxieme caractères est bien un chiffre compris entre 1 et 8
		if (i == 1 && !(chr[i] >= 1 && chr[i] <= 8)) {
			std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
			std::cin >> chr;
			i = 0;
		}
		
		// retourne il n'y a pas de pion sur la case indiquée
		if (i == 1 && emptyBox(toupper(chr[0]) - 64, chr[1], chessboard)){
			std::cout << "Il n'y a pas de pion sur la case indiqué..." << std::endl;
			std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
			std::cin >> chr;
			i = 0;
		}

		// Joue une piece noir alors que c'est au blnc de jouer
		if (i == 1 && (chr[1] == 'w' && white)) {
			std::cout << "Cette pièce ne fait pas partit de votre équipe" << std::endl;
			std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
			std::cin >> chr;
			i = 0;
		}

		// Joue une piece qui n'est pas de son équipe
		if (i == 1 && (chr[1] == 'b' && !white)) {
			std::cout << "Cette pièce ne fait pas partit de votre équipe" << std::endl;
			std::cout << "Quelle est la pièce que vous souhaitez jouer le premier caractère doit etre une lettre la deuxième un numéros entre 1 et 8" << std::endl;
			std::cin >> chr;
			i = 0;
		}

	}

	return Pawn(toupper(chr[0]) - 64, chr[1], whiteorblack(chr, chessboard), chessboard[toupper(chr[0]) - 64][chr[1]]);

}
	bool whiteorblack(char* chr, char chessboard[][8][3]) {
		if (chessboard[toupper(chr[0]) - 64][chr[1]][0] == 'w') {
			return true;
		}
		else {
			return false;
		}

	}
	bool whiteorblack(int x, int y , char chessboard[][8][3]) {
		if (chessboard[x][y][0] == 'w') {
			return true;
		}
		else {
			return false;
		}

	}
	bool emptyBox(int x, int y, char chessboard[8][8][3]) {
		for (int k = 0; k < 2; k++) {
			if(chessboard[x][y][k] == 'O'){
				return true;
			}
		}
		return false;
	}


	bool Pawn::goodMove(int &x, int &y, char chessboard[][8][3])
	{
		if (chessboard[x][y][0] == 'O') {
			Pawn pion = Choix(chessboard, whiteorblack(x, y, chessboard));
			//if (isdntMove) {
				//if(x >)
			//}
		}
		return false;
	}
//return vrais si la piece n'a pas bougé retourne faux si la piece bouge
/*
bool Pawn::isdntMove()
{
	if (move) {
		move = false;
		return true;
	}
	return move;
}


*/
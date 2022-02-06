#include "ChessBoard.h"

void affiche(char chessboard[][8][3]) {
	char a = 'A';
	int nombre = 9;
	for (int i = 1; i < 9; i++) {
		
		for (int letter = 0; letter < 8; letter++) {
			if (letter == 0) {
				std::cout << " " << nombre - i << " ";
			}
			std::cout << "[";
			for (int car = 0; car < 2; car++) {
				std::cout << chessboard[i][letter][car];
			}
			std::cout << "]" << " ";
		}
		std::cout << std::endl;
		
	}
	std::cout << "    ";
	for (int i = 1; i <= 8; i++) {
		std::cout << a++ << "    ";
	}
}

Chessboard::Chessboard(){
	Chessboard::initialisation();
}

void Chessboard::initialisation()
{
	for (int i = 1; i <= 8; i++) {
		for (int letter = 0; letter < 8; letter++) {
			if (i > 2 && i < 7) {
				for (int k = 0; k < 2; k++) {
					chessboard[i][letter][k] = 'O';
				}
			}
			if (i == 7) {
				for (int k = 0; k < 2; k++) {
					chessboard[i][letter][k] = Pawn(letter, i, true, "Pw").name[k];
				}
			}
			if (i == 2) {
				for (int k = 0; k < 2; k++) {
					chessboard[i][letter][k] = Pawn(letter, i, true, "Pb").name[k];
				}
			}
			if (i == 1 || i == 8) {
				for (int k = 0; k < 2; k++) {
					chessboard[i][letter][k] = 'O';
				}
			}
		
		}

	}
}

//#pragma once
#include <iostream>
class Knight {

public:
	Knight(int x, int y, bool white, const char name[3]);
	//void movement(int &x, int &y, Pawn** chessboard[][8]);
	char name[3];

private:
	bool goodMove(int& x, int& y, char chessboard[][8][3]);
	bool isdntMove();


	int x;
	int y;
	bool white;
	bool move;

};
bool whiteorblack(int x, int y, char chessboard[][8][3]);
bool whiteorblack(char* chr, char chessboard[][8][3]);
bool emptyBox(int x, int y, char chessboard[8][8][3]);
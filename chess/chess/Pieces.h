//#pragma once
#include <iostream>

class Pawn {

public:
	Pawn(int x, int y, bool white, const char name[3]);
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
/*
class King : Pawn {
	public:
		King(int &x, int &y, char team);
	private:
		bool goodMove(int &x, int &y);
		bool isMove();
		bool toCheck();
		bool toCheckmate();
		bool pat();

		bool move;
};

class Queen : Pawn {
	public:
		Queen(int x, int y, char team);
	private:
		bool goodMove(int x, int y);
};

class Bishop : Pawn {
public:
	Bishop(int x, int y, char team);

private:
	bool goodMove(int x, int y);
};

class Knight : Pawn {
public:
	Knight(int x, int y, char team);

private:
	bool goodMove(int x, int y);
};

class Rook : Pawn {
public:
	Rook(int x, int y, char team);
private:
	bool goodMove(int x, int y);
};

*/



#include <iostream>
#include "Position.h"


Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Position::get_X()
{
	return this->x;
}

int Position::get_Y()
{
	return this->y;
}

void Position::set_X(int x)
{
	this->x = x;
}

void Position::set_Y(int y)
{
	this->y = y;
}

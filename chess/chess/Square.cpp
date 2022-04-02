#include <cstddef>

#include "Square.h"

Square::Square()
{
	m_occupyingPiece = NULL;
}

Square::Square(const Square& square)
{
	this->m_occupyingPiece = square.m_occupyingPiece;
}

bool Square::occupiedState()
{
	return m_occupyingPiece==NULL? false : true;
}

bool Square::occupySquare(Piece* piece)
{
	if(occupiedState()) return false;
	else m_occupyingPiece = piece;
	return true;
}

Piece* Square::removeOccupyingPiece()
{
	Piece* removed = m_occupyingPiece;
	m_occupyingPiece = NULL;
	return removed;
}

Piece* Square::getOccupyingPiece()
{
	return m_occupyingPiece;
}
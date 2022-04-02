#include "Move.h"

Move::Move(MoveType mType, int fRow, int fCol, int tRow, int tCol, Piece* moved, Piece* captured)
{
	m_type = mType;
	m_fromRow = fRow;
	m_fromCol = fCol;
	m_toRow = tRow;
	m_toCol = tCol;
	m_movePiece = moved;
	m_capturedPiece = captured;
}

Move::Move(const Move& move)
{
	this->m_type = move.m_type;
	this->m_fromRow = move.m_fromRow;
	this->m_fromCol = move.m_fromCol;
	this->m_toRow = move.m_toRow;
	this->m_toCol = move.m_toCol;
	this->m_movePiece = move.m_movePiece;
	this->m_capturedPiece = move.m_capturedPiece;
}

std::pair<int, int> Move::getOriginPosition()
{
	return std::make_pair(m_fromRow, m_fromCol);
}

std::pair<int, int> Move::getDestinationPosition()
{
	return std::make_pair(m_toRow, m_toCol);
}

Piece* Move::getMovedPiece()
{
	return m_movePiece;
}

Piece* Move::getCapturedPiece()
{
	return m_capturedPiece;
}

MoveType Move::getType()
{
	return m_type;
}
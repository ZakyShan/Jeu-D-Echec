#include "Piece.h"

Piece::Piece(PieceType pType, PieceColor pColor)
{
	m_type = pType;
	m_color = pColor;
}

Piece::Piece(const Piece &piece)
{
	this->m_type = piece.m_type;
	this->m_color = piece.m_color;
}

PieceType Piece::getType()
{
	return m_type;
}

PieceColor Piece::getColor()
{
	return m_color;
}
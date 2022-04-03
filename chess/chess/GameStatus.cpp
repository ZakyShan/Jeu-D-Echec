#include <cstddef>

#include "GameStatus.h"

GameStatus::GameStatus()
{
	m_whiteKingMove = false;
	m_blackKingMove = false;
	m_whitePieceEnPassant = NULL;
	m_blackPieceEnPassant = NULL;
	m_whiteFirstColRookMove = false;
	m_whiteLastColRookMove = false;
	m_blackFirstColRookMove = false;
	m_blackLastColRookMove = false;
}

GameStatus::GameStatus(const GameStatus& gameStatus)
{
	this->m_whiteKingMove = gameStatus.m_whiteKingMove;
	this->m_blackKingMove = gameStatus.m_blackKingMove;
	this->m_whitePieceEnPassant = gameStatus.m_whitePieceEnPassant;
	this->m_blackPieceEnPassant = gameStatus.m_blackPieceEnPassant;
	this->m_whiteFirstColRookMove = gameStatus.m_whiteFirstColRookMove;
	this->m_whiteLastColRookMove = gameStatus.m_whiteLastColRookMove;
	this->m_blackFirstColRookMove = gameStatus.m_blackFirstColRookMove;
	this->m_blackLastColRookMove = gameStatus.m_blackLastColRookMove;
}

void GameStatus::setKingMove(PieceColor color)
{
	if(color==PieceColor::WHITE) m_whiteKingMove = true;
	else if(color==PieceColor::BLACK) m_blackKingMove = true;
}

void GameStatus::setPieceEnPassantable(PieceColor color, Piece *piece)
{
	if(color==PieceColor::WHITE) m_whitePieceEnPassant = piece;
	else if(color==PieceColor::BLACK) m_blackPieceEnPassant = piece;
}

void GameStatus::setFirstColRookMove(PieceColor color)
{
	if(color==PieceColor::WHITE) m_whiteFirstColRookMove = true;
	else if(color==PieceColor::BLACK) m_blackFirstColRookMove = true;
}

void GameStatus::setLastColRookMove(PieceColor color)
{
	if(color==PieceColor::WHITE) m_whiteLastColRookMove = true;
	else if(color==PieceColor::BLACK) m_blackLastColRookMove = true;
}

bool GameStatus::isKingMove(PieceColor color)
{
	if(color==PieceColor::WHITE) return m_whiteKingMove;
	else if(color==PieceColor::BLACK) return m_blackKingMove;
}

Piece* GameStatus::pieceEnPassant(PieceColor color)
{
	if(color==PieceColor::WHITE) return m_whitePieceEnPassant;
	else if(color==PieceColor::BLACK) return m_blackPieceEnPassant;
}

bool GameStatus::isFirstColRookMove(PieceColor color)
{
	if(color==PieceColor::WHITE) return m_whiteFirstColRookMove;
	else if(color==PieceColor::BLACK) return m_blackFirstColRookMove;
}

bool GameStatus::isLastColRookMove(PieceColor color)
{
	if(color==PieceColor::WHITE) return m_whiteLastColRookMove;
	else if(color==PieceColor::BLACK) return m_blackLastColRookMove;
}

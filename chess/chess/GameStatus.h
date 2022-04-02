#ifndef GAME_STATUS_H
#define GAME_STATUS_H

#include "Piece.h"
#include "PieceColor.h"

class GameStatus
{
	
	
	public:
		GameStatus();
		GameStatus(const GameStatus& gameStatus);
		
		void setKingMove(PieceColor color);
		void setPieceEnPassantable(PieceColor color, Piece *piece);
		void setFirstColRookMove(PieceColor color);
		void setLastColRookMove(PieceColor color);
		
		bool isKingMove(PieceColor color);
		Piece* pieceEnPassantable(PieceColor color);
		bool isFirstColRookMove(PieceColor color);
		bool isLastColRookMove(PieceColor color);

	private:
		bool m_whiteKingMove;
		bool m_blackKingMove;

		Piece* m_whitePieceEnPassant;
		Piece* m_blackPieceEnPassant;

		bool m_whiteFirstColRookMove;
		bool m_whiteLastColRookMove;
		bool m_blackFirstColRookMove;
		bool m_blackLastColRookMove;
};

#endif
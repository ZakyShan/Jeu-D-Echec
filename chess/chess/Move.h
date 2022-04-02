#ifndef MOVE_H
#define MOVE_H

#include <utility>
#include <cstddef>

#include "Piece.h"
#include "MoveType.h"

class Move
{	
	public:
		Move(MoveType mType, int fRow, int fCol, int tRow, int tCol, Piece* moved, Piece* captured=NULL);
		Move(const Move& move);
		std::pair<int, int> getOriginPosition();
		std::pair<int, int> getDestinationPosition();
		Piece* getMovedPiece();
		Piece* getCapturedPiece();
		MoveType getType();

	private:
		int m_fromRow;
		int m_fromCol;
		Piece* m_movePiece;
		int m_toRow;
		int m_toCol;
		Piece* m_capturedPiece;
		MoveType m_type;
};

#endif
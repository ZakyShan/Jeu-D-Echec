#include "Game.h"

Game::Game()
{
	m_gameplay = new Gameplay();
	m_board = new Board();
	m_status = new GameStatus();
	setInitialPieces(PieceColor::WHITE);
	setInitialPieces(PieceColor::BLACK);
	m_turn = 1;
}

void Game::setInitialPieces(PieceColor color)
{
	int firstRow = (color==PieceColor::WHITE)? m_board->MIN_ROW_INDEX : m_board->MAX_ROW_INDEX;
	int secondRow = (color==PieceColor::WHITE)? m_board->MIN_ROW_INDEX+1 : m_board->MAX_ROW_INDEX-1;
	int firstCol = m_board->MIN_COL_INDEX;
	/* PAWN */
	for(int col = firstCol; col<= m_board->MAX_COL_INDEX; col++)
	{
		m_board->getSquare(secondRow, col)->occupySquare(new Piece(PieceType::PAWN, color));
	}
	/* ROOK */
	m_board->getSquare(firstRow, firstCol)->occupySquare(new Piece(PieceType::ROOK, color));
	m_board->getSquare(firstRow, firstCol+7)->occupySquare(new Piece(PieceType::ROOK, color));
	/* KNIGHT */
	m_board->getSquare(firstRow, firstCol+1)->occupySquare(new Piece(PieceType::KNIGHT, color));
	m_board->getSquare(firstRow, firstCol+6)->occupySquare(new Piece(PieceType::KNIGHT, color));
	/* BISHOP */
	m_board->getSquare(firstRow, firstCol+2)->occupySquare(new Piece(PieceType::BISHOP, color));
	m_board->getSquare(firstRow, firstCol+5)->occupySquare(new Piece(PieceType::BISHOP, color));
	/* QUEEN */
	m_board->getSquare(firstRow, firstCol+3)->occupySquare(new Piece(PieceType::QUEEN, color));
	/* KING */
	m_board->getSquare(firstRow, firstCol+4)->occupySquare(new Piece(PieceType::KING, color));
}

std::stack<Move> Game::getAllLog()
{
	return m_log;
}

Board* Game::getBoard()
{
	return m_board;
}

GameStatus* Game::getGameStatus()
{
	return m_status;
}

std::vector<Move> Game::getValidMoves(int fromRow, int fromCol)
{
	return m_gameplay->getValidMoves(m_status, m_board, m_board->getSquare(fromRow, fromCol)->getOccupyingPiece(), fromRow, fromCol);
}

bool Game::move(int fromRow, int fromCol, int toRow, int toCol)
{
	std::vector<Move> valid = getValidMoves(fromRow, fromCol);
	int sz = valid.size();
	for(int index=0; index<sz; index++)
		if(valid[index].getDestinationPosition().first == toRow && valid[index].getDestinationPosition().second == toCol)
			if(m_gameplay->move(m_status, m_board, valid[index]))
			{
				m_log.push(valid[index]);
				return true;
			}

	return false;
}

PieceColor Game::getPieceColor(int fromRow, int fromCol)
{
	return m_board->getSquare(fromRow, fromCol)->getOccupyingPiece()->getColor();
}

Piece* Game::getPiece(int fromRow, int fromCol)
{
    return m_board->getSquare(fromRow, fromCol)->getOccupyingPiece();
}

bool Game::isSquareOccupied(int fromRow, int fromCol)
{
    return m_board->getSquare(fromRow, fromCol)->occupiedState();
}

bool Game::inCheckState()
{
	return m_gameplay->isCheckState(m_status, m_board, getTurnColor());
}

bool Game::inCheckMateState()
{
	return m_gameplay->isCheckMateState(m_status, m_board, getTurnColor());
}

int Game::getTurn()
{
	return m_turn;
}

void Game::nextTurn()
{
	m_turn++;
	m_status->setPieceEnPassantable(getTurnColor(), NULL);
}

PieceColor Game::getTurnColor()
{
	return m_turn & 1? PieceColor::WHITE : PieceColor::BLACK;
}

bool Game::promote(int row, int col, PieceType type)
{
	return m_gameplay->pawnPromotion(m_board, row, col, type);
}

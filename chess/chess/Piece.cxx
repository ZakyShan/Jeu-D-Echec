/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include <iostream>
#include "Piece.h"
#include "Echiquier.h"
#include <cmath>

using namespace std;

Piece::Piece()
{
  cout << "Constructeur Piece defaut" << endl;
}

Piece::Piece(const Piece & autre)
{
  m_x = autre.m_x;
  m_y = autre.m_y;
  m_white = autre.m_white;
  cout << "Constructeur par copie" << endl;
}

Piece &
Piece::operator=(const Piece & autre)
{
  m_x = autre.m_x;
  m_y = autre.m_y;
  m_white = autre.m_white;
  cout << "Affectation Piece" << endl;
  return *this;
}

Piece::~Piece()
{
  cout << "Destructeur Piece" << endl;
}

Piece::Piece( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
  cout << "Constructeur Piece specialise" << endl;
}

void
Piece::init( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
}

void
Piece::move( int x, int y )
{
  m_x = x;
  m_y = y;
}

int
Piece::x()
{
  return m_x;
}

int
Piece::y()
{
  return m_y;
}

bool
Piece::isWhite()
{
  return m_white;
}


bool
Piece::isBlack()
{
  return !m_white;
}

void
Piece::affiche()
{
  cout << "Piece: x=" << m_x << " y=" << m_y << " "
       << ( m_white ? "blanche" : "noire" ) << endl;
}

bool
Piece::mouvementValide(Echiquier &e, int x, int y)
{
  cout << "mouvementValide Piece" << endl;
  return 0;
}

char
Piece::codePiece()
{
  return (m_white)? 'B' : 'N';
}




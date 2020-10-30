#include "Piece.h"


Piece::Piece(Case ca, bool p)
{
    c = ca;
    pris = p;
}

Piece::Piece(Case ca)
{
    c = ca;
}

Piece::Piece(int colonne , int ligne)
{
    c = Case(colonne,ligne);
}

Piece::Piece()
{
    
}

Case Piece::getCase()
{
    return c;
}

bool Piece::Pris()
{
    return pris;
}

void Piece::setCase(Case ca)
{
    c = ca;
}

void Piece::setPris(bool p)
{
    pris = p;
}
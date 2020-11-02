#include "Piece.h"


Piece::Piece(Case ca, bool p,bool b)
{
    c = ca;
    pris = p;
    blanc = b;
}

Piece::Piece(Case ca , bool b )
{
    c = ca;
    blanc = b;
}

Piece::Piece(int colonne , int ligne , bool b)
{
    c = Case(colonne,ligne);
    blanc = b;
}

Piece::Piece()
{
    
}

Case Piece::getCase()
{
    return c;
}

bool Piece::getPris()
{
    return pris;
}

bool Piece::getBlanc()
{
    return blanc;
}

void Piece::setCase(Case ca)
{
    c = ca;
}

void Piece::setPris(bool p)
{
    pris = p;
}

void Piece::setBlanc(bool b)
{
    blanc = b;
}
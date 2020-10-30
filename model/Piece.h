#ifndef DEF_PIECE
#define DEF_PIECE

#include "Case.h"
#include "Plateau.h"

//class Case;

class  Piece{

protected:
    bool pris;
    Case c;

public:

    Piece( Case ca,bool p);
    Piece(Case ca);
    Piece(int colonne , int ligne);
    Piece();
    Case getCase();
    bool Pris();
    void setPris(bool b);
    void setCase(Case ca);
    virtual std::list<Case> deplacementPossible() = 0;


};

#endif
#ifndef DEF_PIECE
#define DEF_PIECE

#include "Case.h"
#include "Plateau.h"

//class Case;

class  Piece{

protected:
    bool pris;
    Case c;
    bool blanc;

public:

    Piece( Case ca,bool p , bool b);
    Piece(Case ca , bool b);
    Piece(int colonne , int ligne , bool b);
    Piece();
    Case getCase();
    bool getPris();
    bool getBlanc();
    void setPris(bool b);
    void setCase(Case ca);
    void setBlanc(bool b);
    virtual std::vector<Case> deplacementPossible(Plateau p) = 0;


};

#endif
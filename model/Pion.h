#ifndef DEF_PION
#define DEF_PION

#include "Case.h"
#include "Piece.h"

class Pion: public Piece{

public:

    Pion( Case ca,bool p);
    Pion(Case ca);
    Pion(int colonne , int ligne);
    std::list<Case> deplacementPossible();
};

#endif
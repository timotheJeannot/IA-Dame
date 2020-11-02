#ifndef DEF_PION
#define DEF_PION

#include "Case.h"
#include "Piece.h"

class Pion: public Piece{

public:

    Pion( Case ca,bool p,bool b);
    Pion(Case ca , bool b);
    Pion(int colonne , int ligne, bool b);
    Pion();
    std::vector<Case> deplacementPossible(Plateau p);
    std::vector<Case> deplacementPrisePossible(Plateau p); // les deplacements qui font une prise
};

#endif
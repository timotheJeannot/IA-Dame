#ifndef DEF_PION
#define DEF_PION

#include "Case.h"
#include "Plateau.h"

class Pion:Piece{
    bool pris;
    Case c;

public:

    Pion( Case ca,bool p);
    Pion(Case ca);
    Pion(int colonne , int ligne);
    virtual void deplacement(Case vise, Plateau pl) = 0;
};

#endif
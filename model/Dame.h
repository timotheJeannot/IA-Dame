//
// Created by ubuntu on 30/10/2020.
//

#ifndef DEF_DAME_H
#define DEF_DAME_H

#include "Case.h"
#include "Piece.h"



class Dame: public Piece{
public:

    Dame();
    Dame(Case ca,bool p);
    Dame(Case ca);
    Dame(int colonne , int ligne);
    std::list<Case> deplacementPossible();
};


#endif //DEF_DAME_H

//
// Created by ubuntu on 30/10/2020.
//

#ifndef DEF_DAME_H
#define DEF_DAME_H

#include "Case.h"
#include "Piece.h"
#include "Plateau.h"


class Dame: public Piece{
public:

    Dame();
    Dame(Case ca,bool p , bool b);
    Dame(Case ca , bool b);
    Dame(int colonne , int ligne , bool b);
    std::vector<Case> deplacementPossible(Plateau p);
    std::vector<Case> deplacementPrisePossible(Plateau p); // les deplacements qui font une prise
};


#endif //DEF_DAME_H

#ifndef DEF_PION
#define DEF_PION


#include "Piece.h"


class Pion: public Piece{

public:

    Pion( Case ca,bool p,bool b);
    Pion(Case ca , bool b);
    Pion(int colonne , int ligne, bool b);
    Pion();
    //std::vector<Case> deplacementPossible(Plateau p);
    //std::vector<Case> deplacementPrisePossible(Plateau p); // les deplacements qui font une prise
    std::vector<Case> deplacementPossible(std::vector<std::vector<int>> p);
    std::vector<Case> deplacementPrisePossible(std::vector<std::vector<int>> p); // les deplacements qui font une prise
    std::vector<Case> deplacementMajoritaire(std::vector<std::vector<int>> p); // les déplacements poossible qui respectent la prise majoritaire
};

#endif
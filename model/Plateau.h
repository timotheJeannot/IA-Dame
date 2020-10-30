#ifndef DEF_PLATEAU
#define DEF_PLATEAU

#include <list>

#include "Case.h"
#include "Piece.h"
#include "Joueur.h"

class  Plateau{
    std::list<Case> cases;
    Joueur joueurBlanc;
    Joueur joueurNoir;

    public:

    Plateau();
    

};

#endif
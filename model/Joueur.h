#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include <list>
#include<string>

#include "Piece.h"
#include "Plateau.h"

class Joueur {
    std::string couleur;
    Plateau plateau;
    std::list<Piece> pieces;

    public :

    Joueur(std::string c, std::list<Piece> pc);
    Joueur();

    void coup(Piece av , Piece ap);
    
    
};

#endif
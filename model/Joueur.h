#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include <vector>
#include<string>

#include "Piece.h"
#include "Plateau.h"

class Joueur {
    std::string couleur;
    Plateau plateau;
    std::vector<Piece> pieces;

    public :

    Joueur(std::string c, std::vector<Piece> pc);
    Joueur();

    //void coup(Piece p);
    
    
};

#endif
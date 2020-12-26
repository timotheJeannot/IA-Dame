#include "heuristique.h"

struct tree {
    Plateau p; // plateau actuel
    std::vector<Case> listeCoups;   // liste de coups qui permet de passer du plateau du noeud père au plateau actuel ,
                                    // la première case est la position de la piece avant et le reste des cases correspond a ses déplacements
    double value;
    std::vector<tree> childs ; // noeuds fils
};

std::vector<tree> childs (Plateau p , int couleur);


//https://fr.wikipedia.org/wiki/Algorithme_minimax
//lors des appels succesifs à minMax, il faut réutiliser avec un noeud descendant de node , et pas recrée un noeud racine à partir du plateau actuel
// car lors du premier appel à minMax , une partie de l'arbre des états possibles est fait et ainsi on n'a pas besoins de recréer les childs possible à un état courant
void minMax (tree& node,int depth, int couleur, double vNbPieceScore, double vPosPieceScore);

//https://fr.wikipedia.org/wiki/%C3%89lagage_alpha-b%C3%AAta
//optimisation de l'algorithme du min max.
void alphaBeta (tree& node, int depth, int couleur , double& alpha, double& beta, double vNbPieceScore, double vPosPieceScore);
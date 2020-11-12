#ifndef DEF_PLATEAU
#define DEF_PLATEAU

#include <list>
#include <vector> 
#include <algorithm>
#include <iostream>

#include "Case.h"
#include "Piece.h"
#include "Joueur.h"
#include "Pion.h"
#include "Dame.h"
#include "Graph.h"

using namespace std;

class  Plateau{
    std::list<Case> cases;
    Joueur joueurBlanc;
    Joueur joueurNoir;
    //int plateau [10] [10];  // repère , la case en haut à gauche à pour pposition (0,0)
                            // 0 pas de pièce , 1 pion blanc , 2 dame blanc , -1 pion noir , -2 dame noir
    std::vector<std::vector<int>> plateau;


    public:
    Graph graph;
    Plateau();
    Plateau(Plateau *p);
    void printMovePiece();
    std::vector<std::vector<int>>  getPlateau();
    /* pour les méthodes de modication de plateau après un déplacement:
    retour :
        -1 si le coup n'est pas permi 
        0 si plus de prise sont possible après ce coup (sonne la fin du tour)
        1 si des prises sont encore possible après le coup
    modification du platau:
        0 pour les pièces prises lorsque la fonction retourne 0
        3 pour les pièces noirs prises lorsque la fonciton retourne 1 (les pièces sont enlevé à la fin de la rafle)
        -3 pour les pièces blanches prises lorsque la fonciton retourne 1 (les pièces sont enlevé à la fin de la rafle)
    */
    int modifPlateauDeplacementNormal(Pion pion , Case cible);
    int modifPlateauDeplacementNormal(Dame dame , Case cible);
    int modifPlateauDeplacementPrise(Pion pion , Case cible);
    int modifPlateauDeplacementPrise(Dame dame , Case cible);
    void enleverPiecesRafle(); // enlève les 3 , -3 après une fois que le coup est fini
    void listeCheminsPrise(Pion p, std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins , int& max); // Construit la liste de chemins avec prises possible pour le pion
                                                    // chemin et listeChemin sont vide au premier appel de cette méthode
                                                    // chemin correspond au chemin parcouru par le pion a fil des appels récursifs de la méthode
                                                    // listeChemin correpond à la liste des chemins possibles avec des prises pour le pion
                                                    //size est appelé avec 0 pour le premier appel, il représente la taille d'un des chemin avec le plus de prises
    void listeCheminsPrise(Dame d, std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max);
    std::vector<Case> priseMajoritaire(Pion p,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max); // construit les cases qu'un pion peut prendre en prenant en compte la prise majoritaire
    std::vector<Case> priseMajoritaire(Dame p,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max);

    std::vector<std::vector<Case>> PiecesJouable(bool blanc);   // construit les cases disponible des pièces jouable.
                                                                // les pièces jouable sont les premières cases de chaque liste (et le reste des cases de la liste sont les cases dispo)
    string afficheTerminal();  
    
    

};

#endif
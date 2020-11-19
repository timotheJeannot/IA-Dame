#ifndef DEF_PLATEAU
#define DEF_PLATEAU

#include <list>
#include <vector> 
#include <algorithm>
#include <iostream>
#include <map>

#include "Case.h"
#include "Piece.h"
#include "Joueur.h"
#include "Pion.h"
#include "Dame.h"

using namespace std;

class  Plateau{
    /*std::list<Case> cases;
    Joueur joueurBlanc;
    Joueur joueurNoir;*/
    int nbPiecesB;
    int nbPiecesN;
    //int plateau [10] [10];  // repère , la case en haut à gauche à pour pposition (0,0)
                            // 0 pas de pièce , 1 pion blanc , 2 dame blanc , -1 pion noir , -2 dame noir
    std::vector<std::vector<int>> plateau;


    public:
    Plateau();
    Plateau(Plateau *p);
    Plateau(Plateau const& p);
    std::vector<std::vector<int>>  getPlateau();
    int getNbPiecesB();
    int getNbPiecesN();
    /* pour les méthodes de modication de plateau après un déplacement:
    Les vérifications de déplacements sont fait par les méthodes verifDeplacment
    retour :
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
    void listeCheminsPrise(Pion p, std::vector<Case> chemin,std::vector<std::vector<Case>>& listeChemins , int& max); // Construit la liste de chemins avec prises possible pour le pion
                                                    // chemin et listeChemin sont vide au premier appel de cette méthode
                                                    // chemin correspond au chemin parcouru par le pion a fil des appels récursifs de la méthode
                                                    // listeChemin correpond à la liste des chemins possibles avec des prises pour le pion
                                                    //max est appelé avec 0 pour le premier appel, il représente la taille d'un des chemin avec le plus de prises
    void listeCheminsPrise(Dame d, std::vector<Case> chemin,std::vector<std::vector<Case>>& listeChemins, int& max);
    //std::vector<Case> priseMajoritaire(Pion p,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins); // construit les cases qu'un pion peut prendre en prenant en compte la prise majoritaire
    //std::vector<Case> priseMajoritaire(Dame p,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins);


    
    //la méthode suivante retourne une map qui a pour clé les pièces qui peuvent jouer et associe en valeur leurs chemins possible
    std::map<Case,std::vector<std::vector<Case>>> cheminsPiecesJouable(bool blanc);
    /*
     Les deux méthodes suivantes renvoient vrai quand le déplacement est autorisé.
     nbDepla représente combien de déplacements il y a déja eu durant le coup 
    */
    bool verifDeplacement(Pion pion, Case cible,int nbDepla, std::map<Case,std::vector<std::vector<Case>>> cheminsPieces);
    bool verifDeplacement(Dame dame, Case cible,int nbDepla, std::map<Case,std::vector<std::vector<Case>>> cheminsPieces);

    string afficheTerminal();

    void setNbPiecesB(int nbPiecesB);

    void setNbPiecesN(int nbPiecesN);


};

    bool operator== (Plateau opL , Plateau opR);

#endif
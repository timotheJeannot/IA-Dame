#include "../model/Plateau.h"


//plateauPositions prend les mêmes valeurs que les valeurs de postitions à https://www.fladnag.net/downloads/projets/polytech/dames/CHARTON-MOHR-OLLAGNON%20-%20Dames%20-%20Rapport%20final%20-%20Correction%20du%2006-02.pdf
const double plateauPositions[10][10] =    {{0,50,0,25,0,25,0,40,0,75},
                                        {80,0,25,0,25,0,25,0,70,0},
                                        {0,70,0,10,0,10,0,20,0,100},
                                        {100,0,20,0,10,0,10,0,70,0},
                                        {0,70,0,10,0,10,0,20,0,125},
                                        {125,0,20,0,10,0,10,0,70,0},
                                        {0,70,0,10,0,10,0,20,0,100},
                                        {100,0,20,0,10,0,10,0,70,0},
                                        {0,70,0,25,0,25,0,25,0,80},
                                        {75,0,40,0,25,0,25,0,50,0}};

double heuristique1(Plateau p, double vNbPieceScore, double vPosPieceScore); // valeur positive pour les pions blancs et négative pour les pions noirs

double heuristique2(Plateau p, double vNbPieceScore, double vPosPieceScore, double vCouvertureDef, double vCouvertureAtt);
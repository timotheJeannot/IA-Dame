#ifndef TEST_GF_CLIENTTOOLS_H
#define TEST_GF_CLIENTTOOLS_H

#include "../protocole/protocole.h"
#include "../IA/MinMax.h"
#include <random>


int initColor(bool b, int color);
TCoupReq buildCoup(Plateau& p, int couleur, int& err);
TCoupReq buildCoupAlea(Plateau& p, int couleur);
TCoupReq buildCoupHeur1(Plateau& p, int couleur, tree& node,int& choice, double vNbPieceScore , double vPosPieceScore); // i désigne le noeud child qui est choisi dans tree node 
void modifCoupAdv(TCoupReq cr, Plateau& p, int couleur);



#endif //TEST_GF_CLIENTTOOLS_H

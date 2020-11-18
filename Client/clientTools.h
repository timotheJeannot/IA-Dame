#ifndef TEST_GF_CLIENTTOOLS_H
#define TEST_GF_CLIENTTOOLS_H

#include "../protocole/protocole.h"
#include "../model/Plateau.h"

int initColor(bool b, int color);
TCoupReq buildCoup(Plateau& p, int couleur, int& err);
TCoupReq buildCoupAlea(Plateau& p, int couleur);
void modifCoupAdv(TCoupReq cr, Plateau& p, int couleur);


#endif //TEST_GF_CLIENTTOOLS_H

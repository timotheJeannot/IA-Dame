#ifndef TEST_GF_CLIENTTOOLS_H
#define TEST_GF_CLIENTTOOLS_H

#include "../protocole/protocole.h"
#include "../model/Plateau.h"
#include <gf/Vector.h>
#include <random>


int initColor(bool b, int color);
TCoupReq buildCoup(Plateau& p, int couleur, gf::Vector4i vector4I, int& err,int& cont);
TCoupReq buildCoupAlea(Plateau& p, int couleur);
void modifCoupAdv(TCoupReq cr, Plateau& p, int couleur);


#endif //TEST_GF_CLIENTTOOLS_H

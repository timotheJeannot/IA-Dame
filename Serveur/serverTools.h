#ifndef TEST_GF_SERVERTOOLS_H
#define TEST_GF_SERVERTOOLS_H

#include <gf/SocketTypes.h>
#include "../protocole/protocole.h"
#include "../model/Plateau.h"

std::vector<PartieRep> buildRepPartie(TPartieReq pr1, TPartieReq pr2);
TCoupRep buildRepCoup(Plateau& p, TCoupReq cr, int& nbPiece, int couleur);

#endif //TEST_GF_SERVERTOOLS_H


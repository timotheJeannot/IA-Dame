#ifndef TEST_GF_SERVERTOOLS_H
#define TEST_GF_SERVERTOOLS_H


#include "../protocole/protocole.h"
#include "../model/Plateau.h"

std::vector<PartieRep> buildRepPartie(TPartieReq pr1, TPartieReq pr2);
TCoupRep buildRepCoup(Plateau& p, TCoupReq cr, int couleur, std::vector<Plateau>& configs,int& first, int& compteurR2, int compteurR3);

/*  les fonctions suivantes sont utilisé pour détecter la partie nulle : https://fr.wikipedia.org/wiki/Dames#Partie_nulle

    Dans les parties officielles, l'arbitre fait aussi appliquer les règles suivantes : Il y a égalité :

        -quand la même position des pièces se produit pour la troisième fois, et que c'est au même joueur de jouer ;
        -si, durant vingt-cinq coups, aucune prise n'a eu lieu, ni aucun déplacement de pion ;
        -si dans une position à une dame contre trois dames, contre deux dames et un pion, ou contre une dame et deux pions, les deux joueurs ont joué chacun seize coups ;
        -si dans une position à une dame contre deux dames, ou une dame contre une dame, il n'y a plus de phase de jeu.
*/
bool testNulle3Repeat(Plateau p , int couleur , std::vector<Plateau> configs, int first); // 1ere regle
                                // pour la deuxième règle on va la modéliser par un simple compteur dans le serveur
bool r3DetectConfig(Plateau p); // detect la config pour qu'on commence à incrémenter un compteur (troisième règle)
bool testDameVsDame(Plateau p); // dernière regle
bool testPartieNulle(Plateau p , int couleur , std::vector<Plateau> configs, int first , int compteurR2 , int compteurR3); // test si un des 4 cas de match nul est présent
#endif //TEST_GF_SERVERTOOLS_H


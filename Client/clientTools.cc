#include "clientTools.h"

int initColor(bool b, int color) {
    int c;
    if(b)
    {
        c = (color == 1)? 1 : -1;
    }
    else
    {
        c = (color == 1)? -1 : 1;
    }
    return c;
}

TCoupReq buildCoup(Plateau& plateau, int couleur, gf::Vector4i vector4I, int& err, int& cont) {
    TCoupReq coup ;
    coup.idRequest = COUP;
    coup.estBloque = false;
    TPion pion ;
    pion.coulPion = couleur;
    pion.typePion = PION;
    coup.pion = pion;
    coup.propCoup = CONT ;
    std::vector<TCase> deplacements;
    TCase c;
    c.c = vector4I.z;
    c.l = vector4I.w;
    coup.posPionAv = c;

    bool blanc =true;
    if(couleur == -1)
    {
        blanc = false;
    }

    Case c1(c.c, c.l);

    std::map<Case,std::vector<std::vector<Case>>> cheminsPieces = plateau.cheminsPiecesJouable(blanc);

    if(cheminsPieces.size() == 0)
    {
        coup.estBloque= true;
        coup.deplacements = deplacements;
        return coup;
    }


    int nbDeplacement = 0; // représente le nombre de déplacement effectué durant le coup
    std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.find(c1);
    std::vector<std::vector<Case>> listeChemins = it->second;
    int ic = 0;
    Case aCase(vector4I.x,vector4I.y);
    for(int i=0;i<listeChemins.size();i++){
        if(listeChemins.at(i).at(0)==aCase){
            ic=i;
            break;
        }
    }
    int retmodif=0;
    //coup.posPionAp = c;
    switch (plateau.getPlateau()[c.c][c.l]) {
        case 1 :{
            Pion p(c1, true);
            retmodif = plateau.modifPlateauDeplacementNormal(p, aCase);}
            break;
        case 2 :{
            Dame d(c1, true);
            retmodif = plateau.modifPlateauDeplacementNormal(d, aCase);}
            break;
        case -1 :{
            Pion p(c1, false);
            retmodif = plateau.modifPlateauDeplacementNormal(p, aCase);}
            break;
        case -2 :{
            Dame d(c1, false);
            retmodif = plateau.modifPlateauDeplacementNormal(d, aCase);}
            break;
        default:
            break;
    }
    for(int i=0;i<listeChemins[ic].size();i++) {
        switch (plateau.getPlateau()[aCase.getColonne()][aCase.getLigne()]) {
            case 1 : {
                Pion p(aCase, true);
                retmodif = plateau.modifPlateauDeplacementPrise(p, listeChemins[ic].at(i));
            }
                break;
            case 2 : {
                Dame d(aCase, true);
                retmodif = plateau.modifPlateauDeplacementPrise(d, listeChemins[ic].at(i));
            }
                break;
            case -1 : {
                Pion p(aCase, false);
                retmodif = plateau.modifPlateauDeplacementPrise(p, listeChemins[ic].at(i));
            }
                break;
            case -2 : {
                Dame d(aCase, false);
                retmodif = plateau.modifPlateauDeplacementPrise(d, listeChemins[ic].at(i));
            }
                break;
            default:
                break;
        }
        TCase tCase;
        tCase.c = listeChemins[ic].at(i).getColonne();
        tCase.l = listeChemins[ic].at(i).getLigne();
        aCase=listeChemins[ic].at(i);
        deplacements.push_back(tCase);
        nbDeplacement++;
    }
    coup.deplacements = deplacements;
    cont=retmodif;
    return coup;
}
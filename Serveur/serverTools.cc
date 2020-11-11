#include "serverTools.h"
#include "../protocole/protocole.h"

std::vector<PartieRep> buildRepPartie(TPartieReq pr1, TPartieReq pr2) {

    std::vector<PartieRep> partieRep;

    PartieRep rep1 ;
    rep1.err = ERR_OK;
    rep1.nomAdvers = pr2.nomJoueur;
    rep1.validCoulPion = true;

    partieRep.push_back(rep1);

    PartieRep rep2;
    rep2.err = ERR_OK;
    rep2.nomAdvers = pr1.nomJoueur;
    if(pr1.coulPion == pr2.coulPion)
    {
        rep2.validCoulPion = false;
    }
    else
    {
        rep2.validCoulPion = true;
    }

    partieRep.push_back(rep2);

    return partieRep;
}

TCoupRep buildRepCoup(Plateau& plateau, TCoupReq cr, int& nbPieces, int couleur){
    TCoupRep coupRep ;
    std::vector<TCase> deplacements = cr.deplacements;
    TCase posPionAv= cr.posPionAv;
    int x = posPionAv.c;
    int y = posPionAv.l;
    Pion p;
    Dame d ;
    bool isDame = false;
    bool usePieceAdv = false;
    bool testErrCoup = false;
    if (couleur == 1) {
        if(plateau.getPlateau()[x][y] >0)
        {
            usePieceAdv = true;
        }
    }
    else {
        if (plateau.getPlateau()[x][y] <0)
        {
            usePieceAdv = true;
        }
    }

    if (!usePieceAdv)
    {
        if(plateau.getPlateau()[x][y] == -1)
        {
            p = Pion(x,y,false);
        }
        else if(plateau.getPlateau()[x][y] == 1)
        {
            p = Pion(x,y,true);
        }
        else if(plateau.getPlateau()[x][y] == 2)
        {
            d = Dame(x,y,true);
            isDame = true;
        }
        else if(plateau.getPlateau()[x][y] == -2)
        {
            d = Dame(x,y,false);
            isDame = true;
        }

        int size2 = deplacements.size();
        if(isDame)
        {
            TCase cnext = deplacements[0];
            int x2 = cnext.c;
            int y2 = cnext.l;
            Case cible(x2,y2);
            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(d,cible);
            d.setCase(cible);
            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size2 != 1))
            {
                testErrCoup = true;
            }
            if(retModifDeplacement == 1)
            {
                nbPieces --;

                for(int i = 1 ; i <size2; i++)
                {
                    cnext = deplacements[i];
                    x2 = cnext.c;
                    y2 = cnext.l;
                    cible.setColonne(x2);
                    cible.setLigne(y2);
                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(d,cible);
                    d.setCase(cible);
                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                    {
                        testErrCoup = true;
                    }

                }
            }
            nbPieces = nbPieces - size2 +1;
        }
        else
        {
            TCase cnext = deplacements[0];
            int x2 = cnext.c;
            int y2 =  cnext.l;
            Case cible(x2,y2);
            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(p,cible);
            p.setCase(cible);
            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size2 != 1))
            {
                testErrCoup = true;
            }
            if(retModifDeplacement == 1)
            {
                nbPieces --;

                for(int i = 1 ; i <size2; i++)
                {
                    cnext = deplacements[i];
                    x2 = cnext.c;
                    y2 = cnext.l;
                    cible.setColonne(x2);
                    cible.setLigne(y2);
                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(p,cible);
                    p.setCase(cible);
                    cout<<"test de la mort numero 1 (server) : \\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
                    cout<<plateau.afficheTerminal();
                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                    {
                        testErrCoup = true;
                    }
                }
            }
            nbPieces = nbPieces - size2 +1;
        }
        plateau.enleverPiecesRafle();
    }

    if(testErrCoup || usePieceAdv)
    {
        coupRep.err = ERR_COUP;
        coupRep.validCoup = TRICHE ; // je fais pas bien la différence entre ces deux infos du protocole
        //coupRep.propCoup = PERDU; // faut t'il envoyer ça à ce moment ?
    }
    else
    {
        coupRep.err =ERR_OK;
        coupRep.validCoup = VALID;
    }
    if(nbPieces == 0)
    {
        coupRep.propCoup = GAGNE;
    }
    else
    {
        coupRep.propCoup = CONT;
    }
    return coupRep;

}





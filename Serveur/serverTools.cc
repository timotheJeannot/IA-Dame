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

TCoupRep buildRepCoup(Plateau& plateau, TCoupReq cr, int couleur,std::vector<Plateau>& configs, int& first, int& compteurR2, int compteurR3){
    TCoupRep coupRep ;
    std::vector<TCase> deplacements = cr.deplacements;
    int size2 = deplacements.size();
    TCase posPionAv= cr.posPionAv;
    int x = posPionAv.c;
    int y = posPionAv.l;
    Pion p;
    Dame d ;
    bool isDame = false;
    bool usePieceAdv = false;
    bool testErrCoup = false;

    bool blanc =true;
    if(couleur == -1)
    {
        blanc = false;
    }
    cout<<"test  1\n";
    bool testMatchNul = testPartieNulle(plateau,couleur,configs,first,compteurR2,compteurR3);
    cout<<"test  2\n";
    std::map<Case,std::vector<std::vector<Case>>> cheminsPieces = plateau.cheminsPiecesJouable(blanc);
    if(cheminsPieces.size() == 0)
    {
        coupRep.propCoup = PERDU;
        return coupRep;
    }
    cout<<"zertyu\n";
    cout<<plateau.afficheTerminal();
    cout<<"Les pieces jouable sont les suivantes pour le couleur "<<couleur<<": \n";
    for(std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.begin() ; it != cheminsPieces.end() ; it++)
    {
        Case casePiece = it->first;
        cout<<"("<<to_string(casePiece.getColonne())<<","<<to_string(casePiece.getLigne())<<" ";
    }
    cout<<"test  3\n";
    //cout<<"(server ) Les pieces jouable sont les suivantes : \n";
    /*for(std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.begin() ; it != cheminsPieces.end() ; it++)
    {
        Case casePiece = it->first;
        //cout<<"("<<to_string(casePiece.getColonne())<<","<<to_string(casePiece.getLigne())<<")  ";
    }*/
    cout<<"test  4\n";
    Case choixPiece(x,y);
    cout<<"test  5\n";
    auto it = cheminsPieces.find(choixPiece);
    cout<<"test  6\n";
    std::vector<std::vector<Case>> listeChemins = it->second;
    cout<<"test  7\n";
    if(it == cheminsPieces.end())
    {
        testErrCoup = true;
    }
    else
    {
        if(listeChemins[0].size() != size2)
        {
            testErrCoup = true;
        }
    }
    cout<<"test  2\n";
    
    /*
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
                    //cout<<"test de la mort numero 1 (server) : \\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
                    //cout<<plateau.afficheTerminal();
                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                    {
                        testErrCoup = true;
                    }
                }
            }
            nbPieces = nbPieces - size2 +1;
        }
        plateau.enleverPiecesRafle();
    }*/

    if(!testErrCoup && !testMatchNul)
    {
        cout<<"test  2\n";
        if(plateau.getPlateau()[x][y] == couleur)
        {
            cout<<"test  2\n";
            p = Pion(x,y,blanc);
            configs.clear(); // on va bouger un pion , on ne retrouvera jamais la configuration du plateau actuel
            first = 0; // cette ligne est pas trop utile , j'aime pas que first contienne 1 ou -1 si configs est vide.
            compteurR2 = 1 ; // on remet à 1 le compteur pour la 2ieme règle de match nul
        }
        if(plateau.getPlateau()[x][y] == 2*couleur)
        {
            cout<<"test  2\n";
            d = Dame(x,y,blanc);
            isDame = true;
        }
        cout<<"test  2\n";
        int nbDeplacement = 0;
        if(isDame)
        {
            TCase cnext = deplacements[0];
            int x2 = cnext.c;
            int y2 = cnext.l;
            Case cible(x2,y2);
            if(plateau.verifDeplacement(d,cible,nbDeplacement,cheminsPieces) == false)
            {
                testErrCoup = true;
            }
            else
            {
                cout<<"test  2\n";
                Plateau copiePlateau(&plateau);
                int copieNbPieceAdv = 0;
                if(blanc)
                {
                    copieNbPieceAdv = plateau.getNbPiecesN();
                }
                else
                {
                    copieNbPieceAdv = plateau.getNbPiecesB();
                }            
                int retModifDeplacement = plateau.modifPlateauDeplacementNormal(d,cible);
                if(blanc && copieNbPieceAdv > plateau.getNbPiecesN()) // il y a eu une prise, on ne retournera jamais dans la config d'avant
                {
                    configs.clear();
                    first = 0;
                    compteurR2 = 1 ; // on remet à 1 le compteur pour la 2ieme règle de match nul
                }
                else // la dame s'est juste déplacé, il faut sauvegarder l'état du plateau d'avant le déplacement et qui a jouer en premier si c'est le premier coup et augmenter le compteur de la 2ieme règle du match nul (voir serverTools.h pour la règle)
                {
                    configs.push_back(copiePlateau);
                    if(first ==0) // équivalent à configs.size() == 1
                    {
                        first = couleur;
                    }
                    compteurR2 ++;
                }
                
                d.setCase(cible);
                cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
                cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins));
                nbDeplacement++;
                if(retModifDeplacement == 1)
                {

                    for(int i = 1 ; i <size2; i++)
                    {
                        cnext = deplacements[i];
                        x2 = cnext.c;
                        y2 = cnext.l;
                        cible.setColonne(x2);
                        cible.setLigne(y2);
                        if(plateau.verifDeplacement(d,cible,nbDeplacement,cheminsPieces) == false)
                        {
                            testErrCoup = true;
                        }
                        else
                        {
                            retModifDeplacement = plateau.modifPlateauDeplacementPrise(d,cible);
                            it = cheminsPieces.find(d.getCase());
                            d.setCase(cible);
                            cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
                            cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins));
                            nbDeplacement++;
                        }

                    }
                }
                
            }
        }
        else
        {
            TCase cnext = deplacements[0];
            int x2 = cnext.c;
            int y2 = cnext.l;
            Case cible(x2,y2);
            if(plateau.verifDeplacement(p,cible,nbDeplacement,cheminsPieces) == false)
            {
                testErrCoup = true;
                ////cout<<"test de merde  \n";
            }
            else
            {
                int retModifDeplacement = plateau.modifPlateauDeplacementNormal(p,cible);
                ////cout<<"test de merde 2 \n";
                p.setCase(cible);
                cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
                cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins));
                nbDeplacement++;
                if(retModifDeplacement == 1)
                {

                    for(int i = 1 ; i <size2; i++)
                    {
                        cnext = deplacements[i];
                        x2 = cnext.c;
                        y2 = cnext.l;
                        cible.setColonne(x2);
                        cible.setLigne(y2);
                        if(plateau.verifDeplacement(p,cible,nbDeplacement,cheminsPieces) == false)
                        {
                            testErrCoup = true;
                        }
                        else
                        {
                            retModifDeplacement = plateau.modifPlateauDeplacementPrise(p,cible);
                            it = cheminsPieces.find(p.getCase());
                            p.setCase(cible);
                            cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
                            cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins));
                            nbDeplacement++;
                        }

                    }
                }
                
            }
        }
        plateau.enleverPiecesRafle();
    }


    //if(testErrCoup || usePieceAdv)
    if(testErrCoup)
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
    /*if(nbPieces == 0)
    {
        coupRep.propCoup = GAGNE;
    }*/
    if((blanc && plateau.getNbPiecesN() == 0) || !blanc && plateau.getNbPiecesB() == 0)
    {
        coupRep.propCoup = GAGNE;
    }
    else
    {
        if(testMatchNul)
        {
            coupRep.propCoup = NUL;
        }
        else
        {
            coupRep.propCoup = CONT;
        }
    }
    return coupRep;

}

bool testNulle3Repeat(Plateau p , int couleur , std::vector<Plateau> configs, int first)
{
    if(configs.size() < 12)
    {
        return false;
    }
    int nbRepeat = 0;
    int joueurPremierOccurence = 0; // indique quel est le joueur lors de la premiere occurence des répétitions
                                    
    for(int i =0 ; i<configs.size(); i++)
    {
        if(configs[i] == p)
        {
            if(nbRepeat == 0)
            {
                int r = i %2;
                if(r == 0)
                {
                    joueurPremierOccurence = first;
                }
                else
                {
                    joueurPremierOccurence = -first;
                }
                
            }
            nbRepeat ++;

            if(nbRepeat >= 2 && joueurPremierOccurence == couleur)
            {
                return true;
            }
        }
    }
    return false;
}

bool testDameVsDame(Plateau p)
{
    int nbDameB = 0;
    int nbDameN = 0;

    for(int i=0 ; i< 10 ; i++)
    {
        for(int j = 0; j<10 ; j++)
        {
            if(p.getPlateau()[i][j] == 2)
            {
                nbDameB++;
            }
            if(p.getPlateau()[i][j] == -2)
            {
                nbDameN++;
            }
            if(p.getPlateau()[i][j] == 1)
            {
                return false;
            }
            if(p.getPlateau()[i][j] == -1)
            {
                return false;
            }
        }
    }
    if((nbDameB == 2 && nbDameN == 1) || (nbDameN == 2 && nbDameB == 1) || (nbDameB ==1 && nbDameN == 1))
    {
        return true;
    }
    return false;
}

bool r3DetectConfig(Plateau p)
{
    int nbDameB = 0;
    int nbDameN = 0;
    int nbPionB = 0;
    int nbPionN = 0;
    for(int i=0 ; i< 10 ; i++)
    {
        for(int j = 0; j<10 ; j++)
        {
            if(p.getPlateau()[i][j] == 2)
            {
                nbDameB++;
            }
            if(p.getPlateau()[i][j] == -2)
            {
                nbDameN++;
            }
            if(p.getPlateau()[i][j] == 1)
            {
                nbPionB++;
            }
            if(p.getPlateau()[i][j] == -1)
            {
                nbPionN++;
            }
        }
    }

    if((nbDameB ==1 && nbDameN == 3 && nbPionB == 0 && nbPionN == 0)|| (nbDameN ==1 && nbDameB == 3 && nbPionB == 0 && nbPionN == 0))
    {
        return true;
    }

    if((nbDameB ==1 && nbPionB ==0 && nbDameN == 2 && nbPionN ==1)|| (nbDameN ==1 && nbPionN ==0 && nbDameB == 2 && nbPionB ==1))
    {
        return true;
    }

    if((nbDameB ==1 && nbPionB ==0 && nbDameN == 1 && nbPionN ==2)|| (nbDameN ==1 && nbPionN ==0 && nbDameB == 1 && nbPionB ==2))
    {
        return true;
    }


    return false;
}

bool testPartieNulle(Plateau p , int couleur , std::vector<Plateau> configs, int first , int compteurR2 , int compteurR3)
{
    if(compteurR2 == 25 || compteurR3 == 16)
    {
        std::cout<<"-------------------------------------------------\n détection qu'un des compteurs a atteint la valeur indiquant un match nul \n-------------------------------------------------\ncompteurR2 = "<<compteurR2<<endl<<"compteurR3 = "<<compteurR3<<endl;
        return true;
    }
    if(testNulle3Repeat(p ,couleur ,configs, first))
    {
        std::cout<<"-------------------------------------------------\n détection de la première règle de match nul \n-------------------------------------------------\n";
        return true;
    }
    return testDameVsDame(p);
}





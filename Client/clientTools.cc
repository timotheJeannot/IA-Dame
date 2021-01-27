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

TCoupReq buildCoupAlea(Plateau& plateau, int couleur) {
    TCoupReq coup ;
    coup.idRequest = COUP;
    coup.estBloque = false;
    TPion pion ;
    pion.coulPion = couleur;
    pion.typePion = PION;
    coup.pion = pion;
    coup.propCoup = CONT ;
    TCase cnext;
    std::vector<TCase> deplacements;
    bool blanc =true;
    if(couleur == -1)
    {
        blanc = false;
    }

    std::map<Case,std::vector<std::vector<Case>>> cheminsPieces = plateau.cheminsPiecesJouable(blanc);
    if(cheminsPieces.size() == 0)
    {
        coup.estBloque= true;
        coup.deplacements = deplacements;
        return coup;
    }

    cout<<"Les pieces jouable sont les suivantes : \n";
    for(std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.begin() ; it != cheminsPieces.end() ; it++)
    {
        Case casePiece = it->first;
        cout<<"("<<to_string(casePiece.getColonne())<<","<<to_string(casePiece.getLigne())<<") ";
    }



    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0,cheminsPieces.size()-1);
    int r = distribution(generator);
    std::map<Case,std::vector<std::vector<Case>>>::iterator item = cheminsPieces.begin();
    std::advance(item, r);


    Case c1 = item->first;

    cout<<"Case choisie : "<<to_string(c1.getColonne())<<","<<to_string(c1.getLigne())<<")  \n";


    TCase c;
    c.l = c1.getLigne();
    c.c = c1.getColonne();


    coup.posPionAv = c;

    Pion p;
    Dame d;
    bool isDame = false;


    Case choixPiece(c.c, c.l);
    std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.find(choixPiece);


    if(plateau.getPlateau()[c.c][c.l] == couleur)
    {
        p = Pion(c.c,c.l,blanc);
    }
    if(plateau.getPlateau()[c.c][c.l] == 2*couleur)
    {
        d = Dame(c.c,c.l,blanc);
        isDame = true;
    }

    cout<<"Les déplacements qui sont possibles sont : \n";
    std::vector<std::vector<Case>> listeChemins = it->second;
    for(int i = 0 ; i<listeChemins.size(); i++)
    {
        cout<<"("<<to_string(listeChemins[i][0].getColonne())<<","<<to_string(listeChemins[i][0].getLigne())<<")  ";
    }
    cout<<"\n";
    int nbDeplacement = 0; // représente le nombre de déplacement effectué durant le coup


    if(isDame)
    {

        std::uniform_int_distribution<int> distribution2(0,listeChemins.size()-1);
        int r2 = distribution2(generator);


        Case cible(listeChemins[r2][0].getColonne(),listeChemins[r2][0].getLigne());

        cnext.c = listeChemins[r2][0].getColonne();
        cnext.l = listeChemins[r2][0].getLigne();

        int retModif = 0;

        retModif= plateau.modifPlateauDeplacementNormal(d, cible);
        deplacements.push_back(cnext);
        d.setCase(cible);
        cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
        cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins));
        nbDeplacement++;

        while(retModif == 1)
        {
            cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
            cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();

            cout<<"Les déplacements qui sont possibles sont : \n";
            for(int i = 0 ; i<listeChemins.size(); i++)
            {
                cout<<"("<<to_string(listeChemins[i][nbDeplacement].getColonne())<<","<<to_string(listeChemins[i][nbDeplacement].getLigne())<<")  ";
            }
            cout<<"\n";

            std::uniform_int_distribution<int> distribution2(0,listeChemins.size()-1);
            int r2 = distribution2(generator);



            Case cible(listeChemins[r2][nbDeplacement].getColonne(),listeChemins[r2][nbDeplacement].getLigne());



            retModif= plateau.modifPlateauDeplacementPrise(d, cible);
            cnext.c = listeChemins[r2][nbDeplacement].getColonne();
            cnext.l = listeChemins[r2][nbDeplacement].getLigne();
            deplacements.push_back(cnext);
            it = cheminsPieces.find(d.getCase());
            d.setCase(cible);
            cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
            cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins));
            nbDeplacement++;

        }

        plateau.enleverPiecesRafle();

    }
    else
    {

        std::uniform_int_distribution<int> distribution2(0,listeChemins.size()-1);
        int r2 = distribution2(generator);


        Case cible(listeChemins[r2][0].getColonne(),listeChemins[r2][0].getLigne());

        cout<<"Case choisie : "<<to_string(listeChemins[r2][0].getColonne())<<","<<to_string(listeChemins[r2][0].getLigne())<<")  \n";


        int retModif = plateau.modifPlateauDeplacementNormal(p, cible);
        cnext.c = listeChemins[r2][0].getColonne();
        cnext.l = listeChemins[r2][0].getLigne();
        deplacements.push_back(cnext);
        p.setCase(cible);
        cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
        cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins));
        nbDeplacement++;

        while(retModif == 1)
        {
            cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
            cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();

            cout<<"Les déplacements qui sont possibles sont : \n";
            for(int i = 0 ; i<listeChemins.size(); i++)
            {
                cout<<"("<<to_string(listeChemins[i][nbDeplacement].getColonne())<<","<<to_string(listeChemins[i][nbDeplacement].getLigne())<<")  ";
            }

            r2 = distribution2(generator);


            Case cible(listeChemins[r2][nbDeplacement].getColonne(),listeChemins[r2][nbDeplacement].getLigne());


            retModif= plateau.modifPlateauDeplacementPrise(p, cible);
            cnext.c = listeChemins[r2][nbDeplacement].getColonne();
            cnext.l = listeChemins[r2][nbDeplacement].getLigne();
            deplacements.push_back(cnext);
            it = cheminsPieces.find(p.getCase());
            p.setCase(cible);
            cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
            cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins));
            nbDeplacement++;

        }


        plateau.enleverPiecesRafle();


    }
    coup.deplacements = deplacements;
    cout<<"deplacements : ";
    for(int i =0; i < coup.deplacements.size(); i++)
    {
        cout<<to_string(coup.deplacements[i].c)<<" "<<to_string(coup.deplacements[i].l)<<" | |";
    }
    cout<<"\n";
    return coup;

}

void modifCoupAdv(TCoupReq coupAdv, Plateau& plateau, int couleur) {
    std::vector<TCase> deplacementsAdv = coupAdv.deplacements;
    TCase posPionAvAdv = coupAdv.posPionAv;
    int xAdv = posPionAvAdv.c;
    int yAdv = posPionAvAdv.l;
    Pion pAdv;
    Dame dAdv ;
    bool isDameAdv = false;
    if (couleur == 1) {
        if(plateau.getPlateau()[xAdv][yAdv] == -1)
        {
            pAdv = Pion(xAdv,yAdv,false);
        }
        else
        {
            dAdv = Dame(xAdv,yAdv,false);
            isDameAdv = true;
        }
    }
    else if (couleur == -1) {
        if(plateau.getPlateau()[xAdv][yAdv] == 1)
        {
            pAdv = Pion(xAdv,yAdv,true);
        }
        else
        {
            dAdv = Dame(xAdv,yAdv,true);
            isDameAdv = true;
        }
    }


    int size = deplacementsAdv.size();
    if(isDameAdv)
    {
        for(int i = 0 ; i <size; i++)
        {
            TCase cnextAdv = deplacementsAdv[i];
            int x2Adv = cnextAdv.c;
            int y2Adv = cnextAdv.l;
            Case cibleAdv(x2Adv,y2Adv);
            plateau.modifPlateauDeplacementNormal(dAdv,cibleAdv); // ce n'est pas grave si on ne différencie pas les deux types de déplacements, car le serveur à valider le coup
            dAdv.setCase(cibleAdv);

        }
    }
    else
    {
        for(int i = 0 ; i <size; i++)
        {
            TCase cnextAdv = deplacementsAdv[i];
            int x2Adv = cnextAdv.c;
            int y2Adv = cnextAdv.l;
            Case cibleAdv(x2Adv,y2Adv);
            plateau.modifPlateauDeplacementNormal(pAdv,cibleAdv); // ce n'est pas grave si on ne différencies pas les deux types de déplacements, car le serveur à valider le coup
            pAdv.setCase(cibleAdv);
        }
    }
    plateau.enleverPiecesRafle();
}

TCoupReq buildCoupHeur1(Plateau& plateau, int couleur, tree& node, int& choice, double vNbPieceScore, double vPosPieceScore)
{
    TCoupReq coup ;
    coup.idRequest = COUP;
    coup.estBloque = false;
    TPion pion ;
    pion.coulPion = couleur;
    pion.typePion = PION;
    coup.pion = pion;
    coup.propCoup = CONT ;
    TCase cnext;
    std::vector<TCase> deplacements;
    bool blanc =true;
    if(couleur == -1)
    {
        blanc = false;
    }

    //minMax(node,3,couleur);
    /*int alpha = 2147483648;
    int beta = 2147483647;*/
    double alpha = -2147483648;
    double beta = 2147483647;
    alphaBeta(node,3,couleur,alpha,beta,vNbPieceScore,vPosPieceScore);
    //cout<<"node.p = "<<node.p.afficheTerminal()<<endl;
    std::vector<Case> listeCoups;
    for(int i =0 ; i<node.childs.size(); i++)
    {
        if(node.value == node.childs[i].value)
        {
            choice = i;
            listeCoups = node.childs[i].listeCoups;
        }
        /*cout<<"i = "<<i<<endl;
        cout<<"node.childs[i].value = "<<node.childs[i].value<<endl;
        cout<<"node.value = "<<node.value<<endl;*/
    }
    Case cible = listeCoups[0];
    //cout<<"Case choisie : ("<<to_string(cible.getColonne())<<","<<to_string(cible.getLigne())<<")  \n";


    TCase c;
    c.l = cible.getLigne();
    c.c = cible.getColonne();

    coup.posPionAv = c;

    Pion p;
    Dame d;
    bool isDame = false;

    if(plateau.getPlateau()[c.c][c.l] == couleur)
    {
        p = Pion(c.c,c.l,blanc);
    }
    if(plateau.getPlateau()[c.c][c.l] == 2*couleur)
    {
        d = Dame(c.c,c.l,blanc);
        isDame = true;
    }

    int nbDeplacement = 0; // représente le nombre de déplacement effectué durant le coup

    if(isDame)
    {

        cible = listeCoups[1];
        cnext.c = cible.getColonne();
        cnext.l = cible.getLigne();

        int retModif = 0;

        retModif= plateau.modifPlateauDeplacementNormal(d, cible);
        deplacements.push_back(cnext);
        d.setCase(cible);
        nbDeplacement++;

        while(retModif == 1)
        {
            //cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
            //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();

            cible = listeCoups[nbDeplacement+1];

            retModif= plateau.modifPlateauDeplacementPrise(d, cible);
            cnext.c = cible.getColonne();
            cnext.l = cible.getLigne();
            deplacements.push_back(cnext);
            d.setCase(cible);
            nbDeplacement++;
        }

        plateau.enleverPiecesRafle();
    }
    else
    {
        cible = listeCoups[1];

        cnext.c = cible.getColonne();
        cnext.l = cible.getLigne();

        int retModif = 0;

        retModif= plateau.modifPlateauDeplacementNormal(p, cible);
        deplacements.push_back(cnext);
        p.setCase(cible);
        nbDeplacement++;
        while(retModif == 1)
        {
            //cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
            //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();

            cible = listeCoups[nbDeplacement+1];

            retModif= plateau.modifPlateauDeplacementPrise(p, cible);
            cnext.c = cible.getColonne();
            cnext.l = cible.getLigne();
            deplacements.push_back(cnext);
            p.setCase(cible);
            nbDeplacement++;
        }

        plateau.enleverPiecesRafle();
    }
    coup.deplacements = deplacements;
    /*cout<<"deplacements : ";
    for(int i =0; i < coup.deplacements.size(); i++)
    {
        cout<<to_string(coup.deplacements[i].c)<<" "<<to_string(coup.deplacements[i].l)<<" | |";
    }
    cout<<"\n";*/
    return coup;
}

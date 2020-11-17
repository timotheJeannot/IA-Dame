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

TCoupReq buildCoup(Plateau& plateau, int couleur, int& err) {
    TCoupReq coup ;
    coup.idRequest = COUP;
    coup.estBloque = false;
    TPion pion ;
    pion.coulPion = couleur;
    pion.typePion = PION;
    coup.pion = pion;
    coup.propCoup = CONT ;
    
    bool blanc =true;
    if(couleur == -1)
    {
        blanc = false;
    }
    std::map<Case,std::vector<std::vector<Case>>> cheminsPieces = plateau.cheminsPiecesJouable(blanc);

    cout<<"Les pieces jouable sont les suivantes : \n";
    for(std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.begin() ; it != cheminsPieces.end() ; it++)
    {
        Case casePiece = it->first;
        cout<<"("<<to_string(casePiece.getColonne())<<","<<to_string(casePiece.getLigne())<<")  ";
    }


    cout<<"\nDonnez la coordonnée vertical pour le choix de la pièce \n";
    int x;
    cin>>x;
    cout<<"Donnez la coordonnée horizontal pour le choix de la pièce \n";
    int y ;
    cin>>y;

    TCase c;
    c.l = y;
    c.c = x;

    coup.posPionAv = c;

    Pion p;
    Dame d;
    bool isDame = false;

    // les vérifications de choix de la pièce doivent changer
    /*
    if (couleur == 1) {
        if(plateau.getPlateau()[x][y] == 1)
        {
            p = Pion(x,y,true);
        }
        else
        {
            if(plateau.getPlateau()[x][y] == 2)
            {
                d = Dame(x,y,true);
                isDame = true;
            }
            else
            {
                cerr<<"Les coordonnées choisies ne pointent pas sur une piéce \n";
                err = 1;
            }
        }
    }
    else if (couleur == -1) {
        if(plateau.getPlateau()[x][y] == -1)
        {
            p = Pion(x,y, false);
        }
        else
        {
            if(plateau.getPlateau()[x][y] == -2)
            {
                d = Dame(x,y, false);
                isDame = true;
            }
            else
            {
                cerr<<"Les coordonnées choisies ne pointent pas sur une piéce \n";
                err = 1;
            }
        }
    }
    */

    Case choixPiece(x,y);
    std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.find(choixPiece);
    if(it == cheminsPieces.end())
    {
        cerr<<"Les coordonnées choisies ne pointent pas sur une piéce jouable \n";
        err =-1;
    }

    if(plateau.getPlateau()[x][y] == couleur)
    {
        p = Pion(x,y,blanc);
    }
    if(plateau.getPlateau()[x][y] == 2*couleur)
    {
        d = Dame(x,y,blanc);
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

    int x2,y2;

    //coup.posPionAp = c;
    std::vector<TCase> deplacements;
    if(isDame)
    {

        cout<<"Donnez la coordonnée verticale pour le choix de la future position de la pièce \n";
        cin>>x2;
        cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
        cin>>y2;
        Case cible(x2,y2);

        int retModif = 0;
        if(plateau.verifDeplacement(d,cible,nbDeplacement,cheminsPieces) == false)
        {
            cerr<<"Le coup n'est pas autorisé\n";
            err = 1;
        }
        else
        {
            retModif= plateau.modifPlateauDeplacementNormal(d, cible);
            TCase cnext;
            cnext.c = x2;
            cnext.l = y2;
            deplacements.push_back(cnext);
            d.setCase(cible);
            cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
            cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins));
            nbDeplacement++;
        }
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

            cout<<"Donnez la coordonnée verticale pour le choix de la future position de la pièce \n";
            cin>>x2;
            cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
            cin>>y2;
            Case cible(x2,y2);
            if(plateau.verifDeplacement(d,cible,nbDeplacement,cheminsPieces) == false)
            {
                cerr<<"Le coup n'est pas autorisé\n";
                err = 1;
                retModif = 0;
            }
            else
            {
                retModif= plateau.modifPlateauDeplacementPrise(d, cible);
                TCase cnext;
                cnext.c = x2;
                cnext.l = y2;
                deplacements.push_back(cnext);
                d.setCase(cible);
                cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
                cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins));
                nbDeplacement++;
            }
        }


        plateau.enleverPiecesRafle();

        
    }
    else
    {
        /*cout<<"Donnez la coordonnée verticale pour le choix de la future position de la pièce \n";
        cin>>x2;
        cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
        cin>>y2;
        Case cible(x2,y2);
        int retModif= plateau.modifPlateauDeplacementNormal(p, cible);
        TCase cnext;
        cnext.c = x2;
        cnext.l = y2;
        deplacements.push_back(cnext);
        p.setCase(cible);
        while(retModif == 1)
        {
            cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
            cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            cout<<"Donnez la coordonnée verticale pour le choix de la future position de la pièce \n";
            cin>>x2;
            cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
            cin>>y2;
            Case cible(x2,y2);
            retModif= plateau.modifPlateauDeplacementPrise(p, cible);
            cout<<plateau.afficheTerminal();
            TCase cnext;
            cnext.c = x2;
            cnext.l = y2;
            deplacements.push_back(cnext);
            p.setCase(cible);

        }

        plateau.enleverPiecesRafle();

        if(retModif == -1)
        {
            err = 1;
        }*/

        cout<<"Donnez la coordonnée verticale pour le choix de la future position de la pièce \n";
        cin>>x2;
        cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
        cin>>y2;
        Case cible(x2,y2);

        int retModif = 0;
        if(plateau.verifDeplacement(p,cible,nbDeplacement,cheminsPieces) == false)
        {
            cerr<<"Le coup n'est pas autorisé\n";
            err = 1;
        }
        else
        {
            retModif= plateau.modifPlateauDeplacementNormal(p, cible);
            TCase cnext;
            cnext.c = x2;
            cnext.l = y2;
            deplacements.push_back(cnext);
            p.setCase(cible);
            cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
            cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins));
            nbDeplacement++;
        }
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

            cout<<"Donnez la coordonnée verticale pour le choix de la future position de la pièce \n";
            cin>>x2;
            cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
            cin>>y2;
            Case cible(x2,y2);
            if(plateau.verifDeplacement(p,cible,nbDeplacement,cheminsPieces) == false)
            {
                cerr<<"Le coup n'est pas autorisé\n";
                err = 1;
                retModif = 0;
            }
            else
            {
                retModif= plateau.modifPlateauDeplacementPrise(p, cible);
                TCase cnext;
                cnext.c = x2;
                cnext.l = y2;
                deplacements.push_back(cnext);
                p.setCase(cible);
                cheminsPieces.erase(it); // on est obligé de mettre à jour la map, parce que la position dans la clé n'est plus la même et verifDeplacement s'appuie dessus
                cheminsPieces.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins));
                nbDeplacement++;
            }
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

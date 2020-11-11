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


    cout<<"Donnez la coordonnée vertical pour le choix de la pièce \n";
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

    int x2,y2;

    //coup.posPionAp = c;
    std::vector<TCase> deplacements;
    if(isDame)
    {

        cout<<"Donnez la coordonnée verticale pour le choix de la  future position de la pièce \n";
        cin>>x2;
        cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
        cin>>y2;
        Case cible(x2,y2);
        int retModif= plateau.modifPlateauDeplacementNormal(d, cible);
        TCase cnext;
        cnext.c = x2;
        cnext.l = y2;
        deplacements.push_back(cnext);
        d.setCase(cible);
        while(retModif == 1)
        {
            cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
            cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            cout<<"Donnez la coordonnée verticale pour le choix de la  future position de la pièce \n";
            cin>>x2;
            cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
            cin>>y2;
            Case cible(x2,y2);
            retModif= plateau.modifPlateauDeplacementPrise(d, cible);
            TCase cnext;
            cnext.c = x2;
            cnext.l = y2;
            deplacements.push_back(cnext);
            d.setCase(cible);
        }


        plateau.enleverPiecesRafle();

        if(retModif == -1)
        {
            cerr<<"Le coup n'est pas autorisé\n";
            err = 1;
        }
    }
    else
    {
        cout<<"Donnez la coordonnée verticale pour le choix de la  future position de la pièce \n";
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
            cout<<"Donnez la coordonnée verticale pour le choix de la  future position de la pièce \n";
            cin>>x2;
            cout<<"Donnez la coordonnée horizontale pour le choix de la future position de la pièce \n";
            cin>>y2;
            Case cible(x2,y2);
            retModif= plateau.modifPlateauDeplacementPrise(p, cible);
            cout<<"test de la mort numero 1 : \\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
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
        }
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

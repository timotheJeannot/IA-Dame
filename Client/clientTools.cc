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

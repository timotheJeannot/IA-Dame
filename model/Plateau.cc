#include "Plateau.h"

// repère , la case en gaut à gauche à pour position (0,0)
// 0 pas de pièce , 1 pion blanc , 2 dame blanc , -1 pion noir , -2 dame noir
//Plateau::Plateau():graph(){
Plateau::Plateau(){
    
    for(int i =0 ; i< 10 ; i++)
    {
        plateau.push_back(std::vector<int>(10,0));  //std::vector<int>(10,0) = un tableau de taille 10 avec que des 0

        for (int j = 0; j < 4; j++) {
            if (i % 2 != 0 && j % 2 == 0) {
                plateau[i][j] = -1;
            } else if (i % 2 == 0 && j % 2 != 0) {
                plateau[i][j] = -1;
            }
        }

        for (int j = 6; j < 10; j++) {
            if (i % 2 != 0 && j % 2 == 0) {
                plateau[i][j] = 1;
            } else if (i % 2 == 0 && j % 2 != 0) {
                plateau[i][j] = 1;
            }
        }

    }   
    nbPiecesB = 20;
    nbPiecesN = 20;
}

Plateau::Plateau(Plateau *p)
{
    plateau=p->getPlateau();
    nbPiecesN = p->getNbPiecesN();
    nbPiecesB = p->getNbPiecesB();
}

Plateau::Plateau(Plateau const& p)
{
    /*plateau=p.getPlateau();
    nbPiecesN = p.getNbPiecesN();
    nbPiecesB = p.getNbPiecesB();*/
    plateau = p.plateau;
    nbPiecesB = p.nbPiecesB;
    nbPiecesN = p.nbPiecesN;

}


std::vector<std::vector<int>> Plateau::getPlateau()
{
    return plateau;
}

int Plateau::getNbPiecesB()
{
    return nbPiecesB;
}

int Plateau::getNbPiecesN()
{
    return nbPiecesN;
}

int Plateau::modifPlateauDeplacementNormal(Pion pion, Case cible)
{
    /*std::vector<Case> casesDispo = pion.deplacementPossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }*/

    /*std::vector<std::vector<Case>> casesDispo = PiecesJouable(pion.getBlanc());
    int i =0;
    while(casesDispo[i][0] != pion.getCase() && i < casesDispo.size())
    {
        i++;
    }

    if(i== casesDispo.size()) // la piece ne peut pas jouer
    {
        return -1;
    }
    if(pion.getCase() == cible)
    {
        return -1;
    }

    if (std::find(casesDispo[i].begin(), casesDispo[i].end(), cible) == casesDispo[i].end()) // la piece ne peut pas jouer sur la cible indiquer
    {
        return -1;
    }*/


    //Case casePion = pion.getCase();
    int x = pion.getCase().getColonne();
    int y = pion.getCase().getLigne();

    int x2 = cible.getColonne();
    int y2 = cible.getLigne();
    
    plateau[x][y] = 0;
    pion.setCase(cible);
    if(pion.getBlanc())
    {
        plateau[x2][y2] = 1;
        if(x - x2 == 2 || x - x2 == -2) // il y a eu une prise
        {
            nbPiecesN --;
            plateau[x +(x2-x)/2][y+(y2-y)/2] = 3;
            if(y2 == 0) // transformation en dame
            {
                plateau[x2][y2] = 2;
                return 0; // le tour prend fin si il y a eu une tranformation
            }
            std::vector<Case> testPrise = pion.deplacementPrisePossible(this->getPlateau());
            if(testPrise.size() != 0)
            {
                return 1;
            }
        }
        if(y2 == 0) // transformation en dame
        {
            plateau[x2][y2] = 2;
            return 0; // le tour prend fin si il y a eu une tranformation
        }
    }
    else
    {
        plateau[x2][y2] = -1;
        if(x - x2 == 2 || x - x2 == -2) // il y a eu une prise
        {
            nbPiecesB --;
            plateau[x +(x2-x)/2][y+(y2-y)/2] = -3;
            if(y2 == 9) // transformation en dame
            {
                plateau[x2][y2] = -2;
                return 0; // le tour prend fin si il y a eu une tranformation
            }
            std::vector<Case> testPrise = pion.deplacementPrisePossible(this->getPlateau());
            if(testPrise.size() != 0)
            {
                return 1;
            }
        }
        if(y2 == 9) // transformation en dame
        {
            plateau[x2][y2] = -2;
            return 0; // le tour prend fin si il y a eu une tranformation
        }
    }


    return 0;
}

int Plateau::modifPlateauDeplacementPrise(Pion pion, Case cible)
{
    /*std::vector<Case> casesDispo = pion.deplacementPrisePossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }*/

    //Case casePion = pion.getCase();
    int x = pion.getCase().getColonne();
    int y = pion.getCase().getLigne();

    int x2 = cible.getColonne();
    int y2 = cible.getLigne();
    
    plateau[x][y] = 0;
    pion.setCase(cible);
    if(pion.getBlanc())
    {
        plateau[x2][y2] = 1;
        if(x - x2 == 2 || x - x2 == -2) // il y a eu une prise
        {
            nbPiecesN--;
            plateau[x +(x2-x)/2][y+(y2-y)/2] = 3;
            if(y2 == 0) // transformation en dame
            {
                plateau[x2][y2] = 2;
                return 0; // le tour prend fin si il y a eu une tranformation
            }
            std::vector<Case> testPrise = pion.deplacementPrisePossible(this->getPlateau());
            if(testPrise.size() != 0)
            {
                return 1;
            }
        }
        if(y2 == 0) // transformation en dame
        {
            plateau[x2][y2] = 2;
            return 0; // le tour prend fin si il y a eu une tranformation
        }
    }
    else
    {
        plateau[x2][y2] = -1;
        if(x - x2 == 2 || x - x2 == -2) // il y a eu une prise
        {
            nbPiecesB--;
            plateau[x +(x2-x)/2][y+(y2-y)/2] = -3;
            if(y2 == 9) // transformation en dame
            {
                plateau[x2][y2] = -2;
                return 0; // le tour prend fin si il y a eu une tranformation
            }
            std::vector<Case> testPrise = pion.deplacementPrisePossible(this->getPlateau());
            if(testPrise.size() != 0)
            {
                return 1;
            }
        }
        if(y2 == 9) // transformation en dame
        {
            plateau[x2][y2] = -2;
            return 0; // le tour prend fin si il y a eu une tranformation
        }
    }

    return 0;
}

int Plateau::modifPlateauDeplacementNormal(Dame dame, Case cible)
{
    /*std::vector<Case> casesDispo = dame.deplacementPossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }*/

    /*std::vector<std::vector<Case>> casesDispo = PiecesJouable(dame.getBlanc());
    int i =0;
    while(casesDispo[i][0] != dame.getCase() && i < casesDispo.size())
    {
        i++;
    }

    if(i== casesDispo.size()) // la piece ne peut pas jouer
    {
        return -1;
    }
    if(dame.getCase() == cible)
    {
        return -1;
    }

    if (std::find(casesDispo[i].begin(), casesDispo[i].end(), cible) == casesDispo[i].end()) // la piece ne peut pas jouer sur la cible indiquer
    {
        return -1;
    }*/

    int x = dame.getCase().getColonne();
    int y = dame.getCase().getLigne();

    int x2 = cible.getColonne();
    int y2 = cible.getLigne();

    plateau[x][y] = 0;
    dame.setCase(cible);
    if(dame.getBlanc())
    {
        plateau[x2][y2] = 2;

        if(x-x2 <0 && y-y2 <0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y+i] == -1 || plateau[x+i][y+i] == -2)
                {
                    nbPiecesN--;
                    plateau[x+i][y+i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 <0 && y-y2 >0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y-i] == -1 || plateau[x+i][y-i] == -2)
                {
                    nbPiecesN--;
                    plateau[x+i][y-i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 <0)
        {
            for(int i =1 ; i<y2-y ; i++)
            {
                if(plateau[x-i][y+i] == -1 || plateau[x-i][y+i] == -2)
                {
                    nbPiecesN--;
                    plateau[x-i][y+i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 >0)
        {
            for(int i =1 ; i<y-y2 ; i++)
            {
                if(plateau[x-i][y-i] == -1 || plateau[x-i][y-i] == -2)
                {
                    nbPiecesN--;
                    plateau[x-i][y-i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

      
    }
    else
    {
        plateau[x2][y2] = -2;

        if(x-x2 <0 && y-y2 <0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y+i] == 1 || plateau[x+i][y+i] == 2)
                {
                    nbPiecesB--;
                    plateau[x+i][y+i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 <0 && y-y2 >0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y-i] == 1 || plateau[x+i][y-i] == 2)
                {
                    nbPiecesB--;
                    plateau[x+i][y-i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 <0)
        {
            for(int i =1 ; i<y2-y ; i++)
            {
                if(plateau[x-i][y+i] == 1 || plateau[x-i][y+i] == 2)
                {
                    nbPiecesB--;
                    plateau[x-i][y+i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 >0)
        {
            for(int i =1 ; i<y-y2 ; i++)
            {
                if(plateau[x-i][y-i] == 1 || plateau[x-i][y-i] == 2)
                {
                    nbPiecesB--;
                    plateau[x-i][y-i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }
    }
    
    
    return 0;
}

int Plateau::modifPlateauDeplacementPrise(Dame dame, Case cible)
{
    /*std::vector<Case> casesDispo = dame.deplacementPrisePossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }

    if(std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }*/

    int x = dame.getCase().getColonne();
    int y = dame.getCase().getLigne();

    int x2 = cible.getColonne();
    int y2 = cible.getLigne();


    plateau[x][y] = 0;
    dame.setCase(cible);
    if(dame.getBlanc())
    {
        plateau[x2][y2] = 2;

        if(x-x2 <0 && y-y2 <0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y+i] == -1 || plateau[x+i][y+i] == -2)
                {
                    nbPiecesN--;
                    plateau[x+i][y+i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 <0 && y-y2 >0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y-i] == -1 || plateau[x+i][y-i] == -2)
                {
                    nbPiecesN--;
                    plateau[x+i][y-i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 <0)
        {
            for(int i =1 ; i<y2-y ; i++)
            {
                if(plateau[x-i][y+i] == -1 || plateau[x-i][y+i] == -2)
                {
                    nbPiecesN--;
                    plateau[x-i][y+i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 >0)
        {
            for(int i =1 ; i<y-y2 ; i++)
            {
                if(plateau[x-i][y-i] == -1 || plateau[x-i][y-i] == -2)
                {
                    nbPiecesN--;
                    plateau[x-i][y-i] = 3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

      
    }
    else
    {
        plateau[x2][y2] = -2;

        if(x-x2 <0 && y-y2 <0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y+i] == 1 || plateau[x+i][y+i] == 2)
                {
                    nbPiecesB--;
                    plateau[x+i][y+i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 <0 && y-y2 >0)
        {
            for(int i =1 ; i<x2-x ; i++)
            {
                if(plateau[x+i][y-i] == 1 || plateau[x+i][y-i] == 2)
                {
                    nbPiecesB--;
                    plateau[x+i][y-i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 <0)
        {
            for(int i =1 ; i<y2-y ; i++)
            {
                if(plateau[x-i][y+i] == 1 || plateau[x-i][y+i] == 2)
                {
                    nbPiecesB--;
                    plateau[x-i][y+i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        if(x-x2 >0 && y-y2 >0)
        {
            for(int i =1 ; i<y-y2 ; i++)
            {
                if(plateau[x-i][y-i] == 1 || plateau[x-i][y-i] == 2)
                {
                    nbPiecesB--;
                    plateau[x-i][y-i] = -3;
                    std::vector<Case> testPrise = dame.deplacementPrisePossible(this->getPlateau());
                    if(testPrise.size() != 0)
                    {
                        return 1;
                    }
                    return 0;
                }
            }
        }
    }
    
    
    return 0;
}

void Plateau::enleverPiecesRafle()
{
    for(int i =0 ; i < 10 ; i ++)
    {
        for(int j =0 ; j < 10 ; j++)
        {
            if(plateau[i][j] == 3 || plateau[i][j] == -3)
            {
                plateau[i][j] = 0;
            }
        }
    }
}



void Plateau::listeCheminsPrise(Pion p, std::vector<Case> chemin,std::vector<std::vector<Case>>& listeChemins, int& max)
{
    
    std::vector<Case> casesDispoP = p.deplacementPrisePossible(plateau);
    int size = casesDispoP.size();

    for(int i =0 ; i<size ; i++)
    {
        Plateau copie(this);
        std::vector<Case> copieChemin = chemin;
        copieChemin.push_back(casesDispoP[i]);
        int prise = copie.modifPlateauDeplacementPrise(p,casesDispoP[i]);
        if( prise== 1)
        {
            Pion pion(casesDispoP[i],p.getBlanc());
            copie.listeCheminsPrise(pion,copieChemin,listeChemins,max);
        }
        if(prise == 0)
        {
            
            if(copieChemin.size() == max)
            {
                listeChemins.push_back(copieChemin);
            }

            if(copieChemin.size()> max)
            {
                //std::cout<<" dans listeChemins :  caseDispoP[i] = ("<<to_string(casesDispoP[i].getColonne())<<","<<to_string(casesDispoP[i].getLigne())<<")\n";
                //std::cout<<"copieChemin = ";
                for(int j=0; j<copieChemin.size();j++)
                {
                    //std::cout<<" ("<<to_string(copieChemin[j].getColonne())<<","<<to_string(copieChemin[j].getLigne())<<")";
                }
                //std::cout<<endl;
                max = copieChemin.size();
                listeChemins.clear();
                listeChemins.push_back(copieChemin);
                //std::cout<<"listeChemins = \n\t";
                for(int j=0; j<listeChemins.size();j++)
                {
                    for(int k =0 ; k< listeChemins[j].size(); k++)
                    {
                        //std::cout<<" ("<<to_string(listeChemins[j][k].getColonne())<<","<<to_string(listeChemins[j][k].getLigne())<<")";
                    }
                    //std::cout<<"\n\t";
                    
                }
                //std::cout<<endl;
            }
        }
        
    }

}

/*
std::vector<Case> Plateau::priseMajoritaire(Pion p,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins)
{
    int max = 0;
    listeCheminsPrise(p,chemin,listeChemins,max);

    std::vector<Case> ret;
    int size = listeChemins.size();
    for(int i =0 ; i<size ; i++)
    {
        ret.push_back(listeChemins[i][0]);    
    }
    

    return ret;
}*/

void Plateau::listeCheminsPrise(Dame d, std::vector<Case> chemin,std::vector<std::vector<Case>>& listeChemins, int& max)
{
    
    std::vector<Case> casesDispoP = d.deplacementPrisePossible(plateau);
    int size = casesDispoP.size();

    for(int i =0 ; i<size ; i++)
    {
        Plateau copie(this);
        std::vector<Case> copieChemin = chemin;
        copieChemin.push_back(casesDispoP[i]);
        int prise = copie.modifPlateauDeplacementPrise(d,casesDispoP[i]);
        if( prise== 1)
        {
            Dame dame(casesDispoP[i],d.getBlanc());
            copie.listeCheminsPrise(dame,copieChemin,listeChemins,max);
        }
        if(prise == 0)
        {
            if(copieChemin.size() == max)
            {
                listeChemins.push_back(copieChemin);
            }
            if(copieChemin.size()> max)
            {
                max = copieChemin.size();
                listeChemins.clear();
                listeChemins.push_back(copieChemin);
            }
        }
        
    }
}

/*
std::vector<Case> Plateau::priseMajoritaire(Dame d,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins)
{
    int max = 0;
    listeCheminsPrise(d,chemin,listeChemins,max);

    std::vector<Case> ret;
    int size = listeChemins.size();
    for(int i =0 ; i<size ; i++)
    {
            ret.push_back(listeChemins[i][0]); 
    }
    

    return ret;
}
*/

std::map<Case,std::vector<std::vector<Case>>> Plateau::cheminsPiecesJouable(bool blanc){

    std::map<Case,std::vector<std::vector<Case>>>  ret;

    int couleurP = -1;
    if(blanc)
    {
        couleurP = 1;
    }

    int max = 0;
    for(int i =0 ; i<10; i++)
    {
        for(int j =0 ; j<10 ; j++)
        {
            if(plateau[i][j] == 1*couleurP)
            {
                Pion p = Pion(i,j,blanc);
   
                std::vector<Case> chemin;
                std::vector<std::vector<Case>> listeChemins ;

                int size =0;
                listeCheminsPrise(p,chemin,listeChemins,size);

                bool test = true; // vrai si il y a des cases dispo pour la pièce et faux sinon
                
                if(size == max)
                {
                    if(size == 0) // il n'y a pas de prise possible pour la pièce, on lui donne donc les cases de déplacement normal comme cases dispo
                    {
                        std::vector<Case> deplNorm = p.deplacementPossible(plateau);
                        if(deplNorm.size() == 0)
                        {
                            test = false;
                        }

                        for(int i =0 ; i<deplNorm.size() ; i++)
                        {
                            std::vector<Case> toAdd ;
                            toAdd.push_back(deplNorm[i]);
                            listeChemins.push_back(toAdd);
                        }
                    }
                    if(test)
                    {
                        //ret.push_back(listeRet);
                        ret.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins)); 
                    }
                }
                if(size > max) // une pièces à plus de prises possible , il faut annuler tout ce qu'on a mis avant
                {
                    //std::cout<<"yolooooooooooooooooooooooooooooooooooo \n";
                    //std::cout<<"listeChemins = \n\t";
                    for(int j=0; j<listeChemins.size();j++)
                    {
                        for(int k =0 ; k< listeChemins[j].size(); k++)
                        {
                            //std::cout<<" ("<<to_string(listeChemins[j][k].getColonne())<<","<<to_string(listeChemins[j][k].getLigne())<<")";
                        }
                        //std::cout<<"\n\t";
                        
                    }
                    //std::cout<<endl;
                    max = size;
                    ret.clear();
                    ret.insert(std::pair<Case,std::vector<std::vector<Case>>>(p.getCase(),listeChemins)); 
                }
            }
            if(plateau[i][j] == 2*couleurP)
            {
                Dame d = Dame(i,j,blanc);

                std::vector<Case> chemin;
                std::vector<std::vector<Case>> listeChemins ;

                int size =0;
                listeCheminsPrise(d,chemin,listeChemins,size);
                bool test = true; // vrai si il y a des cases dispo pour la pièce et faux sinon
                
                if(size == max)
                {
                    if(size == 0) // il n'y a pas de prise possible pour la pièce, on lui donne donc les cases de déplacement normal comme cases dispo
                    {
                        std::vector<Case> deplNorm = d.deplacementPossible(plateau);
                        if(deplNorm.size() == 0)
                        {
                            test = false;
                        }

                        for(int i =0 ; i<deplNorm.size() ; i++)
                        {
                            std::vector<Case> toAdd ;
                            toAdd.push_back(deplNorm[i]);
                            listeChemins.push_back(toAdd);
                        }
                    }
                    if(test)
                    {
                        //ret.push_back(listeRet);
                        ret.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins)); 
                    }
                }
                if(size > max) // une pièces à plus de prises possible , il faut annuler tout ce qu'on a mis avant
                {
                    max = size;
                    ret.clear();
                    ret.insert(std::pair<Case,std::vector<std::vector<Case>>>(d.getCase(),listeChemins)); 
                }
                
            }            
        }
    }

    return ret;

}

bool Plateau::verifDeplacement(Pion pion, Case cible,int nbDepla, std::map<Case,std::vector<std::vector<Case>>> cheminsPieces)
{
    std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.find(pion.getCase());
    if(it == cheminsPieces.end())
    {
        return false;
    }
    std::vector<std::vector<Case>> chemins = it->second;
    //std::cout<<"dans la fonction qui bug \n";
    //std::cout<<"case cible = ("<<to_string(cible.getColonne())<<","<<to_string(cible.getLigne())<<") nbDéplacement = "<<to_string(nbDepla)<<"\n";
    for(int i =0 ; i<chemins.size();i++)
    {
        for(int j =0 ; j< chemins[i].size() ; j++)
        {
            //std::cout<<" i = "<<to_string(i)<<" j = "<<to_string(j)<<" ("<<to_string(chemins[i][j].getColonne())<<","<<to_string(chemins[i][j].getLigne())<<") yolooooooooooo ";
        }
        if(chemins[i][nbDepla]== cible)
        {
            //std::cout<<"message qui ne s'affiche pas ? \n";
            return true;
        }
    }
    //std::cout<<"\n";
    return false;
}

bool Plateau::verifDeplacement(Dame dame, Case cible,int nbDepla, std::map<Case,std::vector<std::vector<Case>>> cheminsPieces)
{
    std::map<Case,std::vector<std::vector<Case>>>::iterator it = cheminsPieces.find(dame.getCase());
    if(it == cheminsPieces.end())
    {
        return false;
    }
    std::vector<std::vector<Case>> chemins = it->second;
    for(int i =0 ; i<chemins.size();i++)
    {
        if(chemins[i][nbDepla]== cible)
        {
            return true;
        }
    }
    return false;
}

string Plateau::afficheTerminal()
{
    string ret ="\n//////////////////////////////////////////////////////////////////////\n";
    for(int i = 0 ; i<10 ; i ++)
    {
        for(int j = 0 ; j< 10 ; j++)
        {
            if(plateau[j][i] == -1)
            {
                ret = ret + "PN";
            }
            if(plateau[j][i] == -2)
            {
                ret = ret + "DN";
            }
            if(plateau[j][i] == 1)
            {
                ret = ret + "PB";
            }
            if(plateau[j][i] == 2)
            {
                ret = ret + "DB";
            }
            if(plateau[j][i] == 0)
            {
                ret = ret + "--";
            }
            ret = ret + "  |  ";
            //ret = ret + std::to_string(plateau[j][i])+"  |  ";
        }
        ret = ret + "\n---------------------------------------------------------------------\n";
    }
    return ret;
}

/*void Plateau::printMovePiece() {
        graph.renderer.clear();
        graph.printBoard();
        for(int j=0;j<10;j++) {
            for (int i = 0; i < 10; i++) {
                switch(plateau[j][i]){
                    case -2 : {
                        GPiece(gf::Vector2f(graph.begin.height + ((j) * graph.sizeSquare), graph.begin.col + (i * graph.sizeSquare)+5.0f), graph.sizeCircle,
                               gf::Color::Black).render(graph.renderer);
                    }
                    case -1 : {
                        GPiece(gf::Vector2f(graph.begin.height + ((j) * graph.sizeSquare), graph.begin.col + (i * graph.sizeSquare)), graph.sizeCircle,
                               gf::Color::Black).render(graph.renderer);
                    }break;
                    case 2: {
                        GPiece(gf::Vector2f(graph.begin.height + ((j) * graph.sizeSquare), graph.begin.col + (i * graph.sizeSquare)+5.0f), graph.sizeCircle, gf::Color::White).render(graph.renderer);

                    }
                    case 1 : {
                        GPiece(gf::Vector2f(graph.begin.height + ((j) * graph.sizeSquare), graph.begin.col + (i * graph.sizeSquare)), graph.sizeCircle, gf::Color::White).render(graph.renderer);
                    }break;
                }
            }
        }
        graph.renderer.display();
}
*/
bool operator== (Plateau opL, Plateau opR)
{
    for(int i =0 ; i<10 ; i++)
    {
        for(int j =0 ; j<10; j++)
        {
            if(opL.getPlateau()[i][j] != opR.getPlateau()[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

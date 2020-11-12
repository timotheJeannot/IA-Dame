#include "Plateau.h"

// repère , la case en gaut à gauche à pour position (0,0)
// 0 pas de pièce , 1 pion blanc , 2 dame blanc , -1 pion noir , -2 dame noir
Plateau::Plateau():graph(){
    
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
    
}

Plateau::Plateau(Plateau *p)
{
    plateau=p->getPlateau();
}

std::vector<std::vector<int>> Plateau::getPlateau()
{
    return plateau;
}

int Plateau::modifPlateauDeplacementNormal(Pion pion, Case cible)
{
    std::vector<Case> casesDispo = pion.deplacementPossible(this->getPlateau());
    /*std::cout<<"test : "<<std::to_string(casesDispo.size())<<"\n";
    std::cout<<"c1 = ("<<std::to_string(casesDispo[0].getColonne())<<", "<<std::to_string(casesDispo[0].getLigne())<<")\n";
    std::cout<<"c2 = ("<<std::to_string(casesDispo[1].getColonne())<<", "<<std::to_string(casesDispo[1].getLigne())<<")\n";
    std::cout<<"pion = ("<<std::to_string(pion.getCase().getColonne())<<", "<<std::to_string(pion.getCase().getLigne())<<")\n";*/

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }

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
    std::vector<Case> casesDispo = pion.deplacementPrisePossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }

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
    std::vector<Case> casesDispo = dame.deplacementPossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }

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
    std::vector<Case> casesDispo = dame.deplacementPrisePossible(this->getPlateau());

    if (std::find(casesDispo.begin(), casesDispo.end(), cible) == casesDispo.end())
    {
        return -1;
    }

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



void Plateau::listeCheminsPrise(Pion p, std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max)
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
            listeChemins.push_back(copieChemin);
            if(copieChemin.size()> max)
            {
                max = copieChemin.size();
            }
        }
        
    }

}

std::vector<Case> Plateau::priseMajoritaire(Pion p,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max)
{
    listeCheminsPrise(p,chemin,listeChemins,max);

    std::vector<Case> ret;
    int size = listeChemins.size();
    for(int i =0 ; i<size ; i++)
    {
        if(listeChemins[i].size() == max)
        {
            ret.push_back(listeChemins[i][0]); 
        }
    }
    

    return ret;
}

void Plateau::listeCheminsPrise(Dame d, std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max)
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
            listeChemins.push_back(copieChemin);
            if(copieChemin.size()> max)
            {
                max = copieChemin.size();
            }
        }
        
    }
}

std::vector<Case> Plateau::priseMajoritaire(Dame d,std::vector<Case> chemin,std::vector<std::vector<Case>> listeChemins, int& max)
{
    listeCheminsPrise(d,chemin,listeChemins,max);

    std::vector<Case> ret;
    int size = listeChemins.size();
    for(int i =0 ; i<size ; i++)
    {
        if(listeChemins[i].size() == max)
        {
            ret.push_back(listeChemins[i][0]); 
        }
    }
    

    return ret;
}

std::vector<std::vector<Case>> Plateau::PiecesJouable(bool blanc)
{
    std::vector<std::vector<Case>> ret;

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
            
                int size = 0;
                std::vector<Case> chemin;
                std::vector<std::vector<Case>> listeChemins ;

                std::vector<Case> priseMaj = priseMajoritaire(p,chemin,listeChemins,size);
                std::vector<Case> listeRet ;
                listeRet.push_back(p.getCase());
                listeRet.insert(listeRet.end(),priseMaj.begin(),priseMaj.end());
                bool test = true; // vrai si il y a des cases dispo pour la pièce et faux sinon
                
                if(size == max)
                {
                    if(size == 0) // il n'y a pas de prise possible, pour la pièce, on lui donne donc les cases de déplacement normal comme cases dispo
                    {
                        std::vector<Case> deplNorm = p.deplacementPossible(plateau);
                        if(deplNorm.size() == 0)
                        {
                            test = false;
                        }
                        listeRet.insert(listeRet.end(),deplNorm.begin(),deplNorm.end());
                    }
                    if(test)
                    {
                        ret.push_back(listeRet);
                    }
                }
                if(size > max) // une pièces à plus de prises possible , il faut annuler tout ce qu'on a mis avant
                {
                    max = size;
                    ret.clear();
                    ret.push_back(listeRet);
                }
            }
            if(plateau[i][j] == 2*couleurP)
            {
                Dame d = Dame(i,j,blanc);

                int size = 0;
                std::vector<Case> chemin;
                std::vector<std::vector<Case>> listeChemins ;
                
                std::vector<Case> priseMaj = priseMajoritaire(d,chemin,listeChemins,size);
                std::vector<Case> listeRet ;
                listeRet.push_back(d.getCase());
                listeRet.insert(listeRet.end(),priseMaj.begin(),priseMaj.end());
                bool test = true; // vrai si il y a des cases dispo pour la pièce et faux sinon
                
                if(size == max)
                {
                    if(size == 0) // il n'y a pas de prise possible, pour la pièce, on lui donne donc les cases de déplacement normal comme cases dispo
                    {
                        std::vector<Case> deplNorm = d.deplacementPossible(plateau);
                        if(deplNorm.size() == 0)
                        {
                            test = false;
                        }
                        listeRet.insert(listeRet.end(),deplNorm.begin(),deplNorm.end());
                    }
                    if(test)
                    {
                        ret.push_back(listeRet);
                    }
                }
                if(size > max) // une pièces à plus de prises possible , il faut annuler tout ce qu'on a mis avant
                {
                    max = size;
                    ret.clear();
                    ret.push_back(listeRet);
                }
                
            }            
        }
    }

    return ret;
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

void Plateau::printMovePiece() {
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

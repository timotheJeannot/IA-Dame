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


//    plateau[1][0] = -1;
//    plateau[3][0] = -1;
//    plateau[5][0] = -1;
//    plateau[7][0] = -1;
//    plateau[9][0] = -1;
//    plateau[0][1] = -1;
//    plateau[2][1] = -1;
//    plateau[4][1] = -1;
//    plateau[6][1] = -1;
//    plateau[8][1] = -1;
//    plateau[1][2] = -1;
//    plateau[3][2] = -1;
//    plateau[5][2] = -1;
//    plateau[7][2] = -1;
//    plateau[9][2] = -1;
//    plateau[0][3] = -1;
//    plateau[2][3] = -1;
//    plateau[4][3] = -1;
//    plateau[6][3] = -1;
//    plateau[8][3] = -1;
//
//    plateau[1][6] = 1;
//    plateau[3][6] = 1;
//    plateau[5][6] = 1;
//    plateau[7][6] = 1;
//    plateau[9][6] = 1;
//    plateau[0][7] = 1;
//    plateau[2][7] = 1;
//    plateau[4][7] = 1;
//    plateau[6][7] = 1;
//    plateau[8][7] = 1;
//    plateau[1][8] = 1;
//    plateau[3][8] = 1;
//    plateau[5][8] = 1;
//    plateau[7][8] = 1;
//    plateau[9][8] = 1;
//    plateau[0][9] = 1;
//    plateau[2][9] = 1;
//    plateau[4][9] = 1;
//    plateau[6][9] = 1;
//    plateau[8][9] = 1;


   
    
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

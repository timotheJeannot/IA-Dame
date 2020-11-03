#include "Pion.h"

Pion::Pion(){

}
Pion::Pion(Case ca,bool p , bool b):Piece(ca,p,b){

}
Pion::Pion(Case ca , bool b):Piece(ca,b){

}
Pion::Pion(int colonne , int ligne , bool b):Piece(colonne, ligne,b){

}


// on ne va pas prendre en compte la prise majoritaire pour l'instant
std::vector<Case> Pion::deplacementPossible(std::vector<std::vector<int>> p){
    /*
    std::list<Case> listCase;
    for(int i=c.getColonne()-1;i>0;i--){
        //DIagonale en haut gauche
        if(c.getLigne()-(c.getColonne()-i)){
            listCase.push_back(Case(i,c.getLigne()-(c.getColonne()-i)));
        }
        //DIagonale en bas gauche
        if(c.getLigne()+(c.getColonne()-i)<10){
            listCase.push_back(Case(i,c.getLigne()+(c.getColonne()-i)));
        }
    }
    for(int i=c.getColonne()+1;i<10;i++){
        //DIagonale en haut droite
        if(c.getLigne()-(c.getColonne()-i)){
            listCase.push_back(Case(i,c.getLigne()-(c.getColonne()-i)));
        }
        //DIagonale en bas droite
        if(c.getLigne()+(c.getColonne()-i)<10){
            listCase.push_back(Case(i,c.getLigne()+(c.getColonne()-i)));
        }
    }
    */

    std::vector<Case> listCase;
    std::vector<std::vector<int>> plateau = p;//p.getPlateau();
    
    //---- cas des 4 prises possibles -----------//
    bool testPrise = false;
    if(c.getColonne()+1 <=9 &&  c.getLigne()+1 <=9)
    {
        if((plateau[c.getColonne()+1][c.getLigne()+1] <0 && blanc) || (plateau[c.getColonne()+1][c.getLigne()+1] >0 && blanc == false) )
        {
            if(c.getColonne()+2 <=9 && c.getLigne()+2 <=9)
            {
                if(plateau[c.getColonne()+2][c.getLigne()+2 ] == 0)
                {
                    int x1 = c.getColonne()+2;
                    int y1 = c.getLigne()+2;
                    Case casePush (x1,y1);
                    
                    listCase.push_back(casePush);
                    testPrise = true;
                }
            }
        }
    }

    if(c.getColonne()-1 >=0 &&  c.getLigne()+1 <=9)
    {
        if((plateau[c.getColonne()-1][c.getLigne()+1] <0 && blanc) || (plateau[c.getColonne()-1][c.getLigne()+1] >0 && blanc == false) )
        {
            if(c.getColonne() -2 >=0 && c.getLigne()+2 <=9)
            {
                if(plateau[c.getColonne()-2][c.getLigne()+2 ] == 0)
                {
                    listCase.push_back(Case(c.getColonne()-2,c.getLigne()+2));
                    testPrise = true;
                }
            }
        }
    }

    if(c.getColonne()-1 >=0 &&  c.getLigne()-1 >=0)
    {
        if((plateau[c.getColonne()-1][c.getLigne()-1] <0 && blanc) || (plateau[c.getColonne()-1][c.getLigne()-1] >0 && blanc == false) )
        {
            if(c.getColonne() -2 >=0 && c.getLigne()-2 >=0)
            {
                if(plateau[c.getColonne()-2][c.getLigne()-2 ] == 0)
                {
                    listCase.push_back(Case(c.getColonne()-2,c.getLigne()-2));
                    testPrise = true;
                }
            }
        }
    }

    if(c.getColonne()+1 <=9 &&  c.getLigne()-1 >=0)
    {
        if((plateau[c.getColonne()+1][c.getLigne()-1] <0 && blanc) || (plateau[c.getColonne()+1][c.getLigne()-1] >0 && blanc == false) )
        {
            if(c.getColonne() +2 <=9 && c.getLigne()-2 >=0)
            {
                if(plateau[c.getColonne()+2][c.getLigne()-2 ] == 0)
                {
                    listCase.push_back(Case(c.getColonne()+2,c.getLigne()-2));
                    testPrise = true;
                }
            }
        }
    }
    
   if(testPrise ==false) // si il y a une prise, on est obliger de prendre 
   {
        // il faut différencier aller de l'avant selon la couleur
        
        if(blanc == false)
        {
            if(c.getColonne()+1 <= 9 && c.getLigne()+1 <= 9)
            {
                if(plateau[c.getColonne()+1][c.getLigne()+1] == 0)
                {
                    listCase.push_back(Case(c.getColonne()+1,c.getLigne()+1));
                }
            }
            if(c.getColonne() -1 >=0 && c.getLigne()+1 <= 9)
            {
                if(plateau[c.getColonne()-1][c.getLigne()+1] == 0)
                {
                    listCase.push_back(Case(c.getColonne()-1,c.getLigne()+1));
                }
            }
        }
        else
        {
            if(c.getColonne()+1 <= 9 && c.getLigne()-1 >= 0)
            {
                if(plateau[c.getColonne()+1][c.getLigne()-1] == 0)
                {
                    //std::cout<<"test 1 yolo : ("<<std::to_string(c.getColonne()+1)<<", "<<std::to_string(c.getLigne()-1)<<")\n";
                    listCase.push_back(Case(c.getColonne()+1,c.getLigne()-1));
                }
            }

            if(c.getColonne()-1 >= 0 && c.getLigne()-1 >= 0)
            {
                if(plateau[c.getColonne()-1][c.getLigne()-1] == 0)
                {
                    //std::cout<<"test 2 yolo : ("<<std::to_string(c.getColonne()-1)<<", "<<std::to_string(c.getLigne()-1)<<")\n";
                    listCase.push_back(Case(c.getColonne()-1,c.getLigne()-1));
                }
            }
        }
        
   }

   return listCase;
}

std::vector<Case> Pion::deplacementPrisePossible (std::vector<std::vector<int>> p)
{
    std::vector<Case> listCase;
    std::vector<std::vector<int>> plateau = p;//p.getPlateau();
    
    //---- cas des 4 prises possibles -----------//
    if(c.getColonne()+1 <=9 &&  c.getLigne()+1 <=9)
    {
        if((plateau[c.getColonne()+1][c.getLigne()+1] <0 && blanc) || (plateau[c.getColonne()+1][c.getLigne()+1] >0 && blanc == false) )
        {
            if(c.getColonne()+2 <=9 && c.getLigne()+2 <=9)
            {
                if(plateau[c.getColonne()+2][c.getLigne()+2] == 0)
                {
                    listCase.push_back(Case(c.getColonne()+2,c.getLigne()+2));
                }
            }
        }
    }

    if(c.getColonne()-1 >=0 &&  c.getLigne()+1 <=9)
    {
        if((plateau[c.getColonne()-1][c.getLigne()+1] <0 && blanc) || (plateau[c.getColonne()-1][c.getLigne()+1] >0 && blanc == false) )
        {
            if(c.getColonne() -2 >=0 && c.getLigne()+2 <=9)
            {
                if(plateau[c.getColonne()-2][c.getLigne()+2 ] == 0)
                {
                    listCase.push_back(Case(c.getColonne()-2,c.getLigne()+2));
                }
            }
        }
    }

    if(c.getColonne()-1 >=0 &&  c.getLigne()-1 >=0)
    {
        if((plateau[c.getColonne()-1][c.getLigne()-1] <0 && blanc) || (plateau[c.getColonne()-1][c.getLigne()-1] >0 && blanc == false) )
        {
            if(c.getColonne() -2 >=0 && c.getLigne()-2 >=0)
            {
                if(plateau[c.getColonne()-2][c.getLigne()-2] == 0)
                {
                    listCase.push_back(Case(c.getColonne()-2,c.getLigne()-2));
                }
            }
        }
    }

    if(c.getColonne()+1 <=9 &&  c.getLigne()-1 >=0)
    {
        if((plateau[c.getColonne()+1][c.getLigne()-1] <0 && blanc) || (plateau[c.getColonne()+1][c.getLigne()-1] >0 && blanc == false) )
        {
            if(c.getColonne() +2 <=9 && c.getLigne()-2 >=0)
            {
                if(plateau[c.getColonne()+2][c.getLigne()-2 ] == 0)
                {
                    listCase.push_back(Case(c.getColonne()+2,c.getLigne()-2));
                }
            }
        }
    }

    return listCase;
}
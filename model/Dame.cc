//
// Created by ubuntu on 30/10/2020.
//

#include "Dame.h"

Dame::Dame(){

}
Dame::Dame(Case ca,bool p):Piece(ca,p){

}
Dame::Dame(Case ca):Piece(ca){

}
Dame::Dame(int colonne , int ligne):Piece(colonne, ligne){

}
std::list<Case> Dame::deplacementPossible(){
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


}
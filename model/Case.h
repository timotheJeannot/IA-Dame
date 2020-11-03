#ifndef DEF_CASE
#define DEF_CASE

#include<iostream>

class Case{
    int colonne; // ligne et colonne sont >= 0 et <= 9 case en haut à gauche a pour position (0,0)
    int ligne;

public :

    Case(int x, int y);
    Case(Case *ca);
    Case();
    //~Case();
    int getColonne();
    int getLigne();
    void setColonne(int x);
    void setLigne(int y);

    
};

bool operator== (Case opL , Case opR);

#endif
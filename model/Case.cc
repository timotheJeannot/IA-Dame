#include "Case.h"


Case::Case(int x , int y){
    colonne = x;
    ligne = y;
}

Case::Case(Case &ca){
    colonne = ca.getColonne();
    ligne = ca.getLigne();
}

Case::Case()
{
}

int Case::getColonne()
{
    return colonne;
}

int Case::getLigne()
{
    return ligne;
}

void Case::setColonne(int x)
{
    colonne = x;
}

void Case::setLigne(int y )
{
    ligne = y;
}


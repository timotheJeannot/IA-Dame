#include "Case.h"


Case::Case(int x , int y){
    colonne = x;
    ligne = y;
}

/*Case::Case( Case &ca){
    colonne = ca.getColonne();
    ligne = ca.getLigne();
}*/

Case::Case( Case *ca){
    colonne = ca->getColonne();
    ligne = ca->getLigne();
}


Case::Case()
{
}

int Case::getColonne() const {
    return colonne;
}

int Case::getLigne() const {
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

bool operator==(Case opL, Case opR)
{
    if(opL.getColonne() == opR.getColonne() && opL.getLigne() == opR.getLigne() )
    {
        return true;
    }
    return false;
}

bool operator!=(Case opL, Case opR)
{
    if(opL.getColonne() != opR.getColonne() || opL.getLigne() != opR.getLigne())
    {
        return true;
    }
    return false;
}

bool operator<(Case opL, Case opR)
{
    if(opL.getLigne()<opR.getLigne())
    {
        return true;
    }
    if(opL.getLigne()>opR.getLigne())
    {
        return false;
    }
    if(opL.getColonne()<opR.getColonne())
    {
        return true;
    }
    return false;
}


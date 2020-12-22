#include "MinMax.h"

std::vector<tree> childs (Plateau p , int couleur) {

    bool c = true;
    if(couleur == -1)
    {
        c = false;
    }
    std::vector<tree> ret;
    std::map<Case,std::vector<std::vector<Case>>> piecesJouable = p.cheminsPiecesJouable(c);
    std::vector<std::vector<int>> plateau = p.getPlateau();

    for(std::map<Case,std::vector<std::vector<Case>>>::iterator it = piecesJouable.begin() ; it != piecesJouable.end() ; it++)
    {
        //Case Piece = it->first;
        std::vector<std::vector<Case>> chemins= it->second;

        for(int j =0 ; j<chemins.size();j++)
        {
            Case Piece = it->first;
            Plateau childP (p);
            if(plateau[Piece.getColonne()][Piece.getLigne()] == 2*couleur)
            {
                Dame dame(Piece.getColonne(),Piece.getLigne(),c);
                childP.modifPlateauDeplacementNormal(dame,chemins[j][0]);
            }
            if(plateau[Piece.getColonne()][Piece.getLigne()] == couleur)
            {
                Pion pion(Piece.getColonne(),Piece.getLigne(),c);
                childP.modifPlateauDeplacementNormal(pion,chemins[j][0]);
            }

            for(int k=1 ; k<chemins[j].size() ; k++)
            {
                Piece = chemins[j][k-1];
                if(childP.getPlateau()[Piece.getColonne()][Piece.getLigne()] == 2*couleur)
                {
                    Dame dame(Piece.getColonne(),Piece.getLigne(),c);
                    childP.modifPlateauDeplacementPrise(dame,chemins[j][k]);
                }
                if(childP.getPlateau()[Piece.getColonne()][Piece.getLigne()] == couleur)
                {
                    Pion pion(Piece.getColonne(),Piece.getLigne(),c);
                    childP.modifPlateauDeplacementPrise(pion,chemins[j][k]);
                }

            }
            childP.enleverPiecesRafle();
            tree child;
            child.p = childP;
            child.listeCoups = chemins[j];
            child.listeCoups.insert(child.listeCoups.begin(), it->first);
            ret.push_back(child);        
        }
    }
    return ret;
}

void minMax (tree& node,int depth, int couleur)
{
    if(depth == 0 || node.p.getNbPiecesB() == 0 || node.p.getNbPiecesN() == 0) // prise en compte du match nul ?
    {
         node.value =heuristique1(node.p);
         return;
    }
    if(couleur == 1)
    {
        node.value = -2147483648;
        if(node.childs.size() == 0)
        {
            //cout<<"test childs 0 \n";
            node.childs = childs(node.p,couleur);
            //cout<<"test childs 1 \n";
        }
        for( int i =0 ; i<node.childs.size(); i++)
        {
            minMax(node.childs[i], depth -1 ,couleur*(-1));
            if(node.value < node.childs[i].value)
            {
                node.value  = node.childs[i].value;
            }
        }
        return;
    }
    else
    {
        node.value = 2147483647;
        if(node.childs.size() == 0)
        {
            node.childs = childs(node.p,couleur);
        }
        for( int i =0 ; i<node.childs.size(); i++)
        {
            minMax(node.childs[i], depth -1 ,couleur*(-1));
            if(node.value > node.childs[i].value)
            {
                node.value  = node.childs[i].value;
            }
        }
    }    
}

void alphaBeta (tree& node, int depth, int couleur , int& alpha, int &beta)
{
    if(depth == 0 || node.p.getNbPiecesB() == 0 || node.p.getNbPiecesN() == 0) // prise en compte du match nul ?
    {
         node.value =heuristique1(node.p);
         return;
    }

    if(couleur == 1)
    {
        node.value = -2147483648;
        if(node.childs.size() == 0)
        {
            node.childs = childs(node.p,couleur);
        }
        for( int i =0 ; i<node.childs.size(); i++)
        {
            alphaBeta(node.childs[i], depth -1 ,couleur*(-1),alpha,beta);
            if(node.value < node.childs[i].value)
            {
                node.value  = node.childs[i].value;
            }
            if(node.value >= beta)
            {
                return;
            }
            if(node.value > alpha)
            {
                alpha = node.value;
            }
        }
    }
    else
    {
        node.value = 2147483647;
        if(node.childs.size() == 0)
        {
            node.childs = childs(node.p,couleur);
        }
        for( int i =0 ; i<node.childs.size(); i++)
        {
            alphaBeta(node.childs[i], depth -1 ,couleur*(-1),alpha,beta);
            if(node.value > node.childs[i].value)
            {
                node.value  = node.childs[i].value;
            }
            if(node.value <= alpha)
            {
                return;
            }
            if(node.value < beta)
            {
                beta = node.value;
            }
        }
    }
    

}









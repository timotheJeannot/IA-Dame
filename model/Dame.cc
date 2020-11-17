//
// Created by ubuntu on 30/10/2020.
//

#include "Dame.h"


Dame::Dame(){

}
Dame::Dame(Case ca,bool p, bool b):Piece(ca,p,b){

}
Dame::Dame(Case ca,bool b):Piece(ca,b){

}
Dame::Dame(int colonne , int ligne, bool b):Piece(colonne, ligne,b){

}



//http://www.ffjd.fr/Web/index.php?page=reglesdujeu
// cette fonction indique dans une liste les cases qui sont disponibles pour un déplacement d'une dame sur les 4 diagonales.
//attention on ne prend pas en compte la prise majoritaire pour l'instant. (voir le lien)
std::vector<Case> Dame::deplacementPossible(std::vector<std::vector<int>> p){
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
    std::vector<std::vector<int>> plateau = p;//p.getPlateau();

    ///// ------------ Diagonal en haut à gauche  ----------------- //////////

    int longueurDiagonalHG ;
    std::vector<Case> diagonalHG;
    bool priseDiagonalHG = false; // si il y a une prise qui est possible sur la diagonal, il ne faut pas mettre les cases avant la prise (diagonalHG) comme cases dispo

    if(c.getColonne() <= c.getLigne())
    {
        longueurDiagonalHG = c.getColonne();
    }
    else
    {
        longueurDiagonalHG = c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalHG ; i++)
    {
        // on regarde si la case est libre
        if(plateau[c.getColonne()-i][c.getLigne()-i] == 0)
        {
            diagonalHG.push_back(Case(c.getColonne()-i ,c.getLigne()-i));
        }
        else
        {
            // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
            if((plateau[c.getColonne()-i][c.getLigne()-i] >0 && blanc ) || (plateau[c.getColonne()-i][c.getLigne()-i] <0 && blanc == false))
            {
                break; // les cases dispo pour cette diagonal s'arréte là
            }
            
            //on regarde si il y a une pièce adverse
            if((plateau[c.getColonne()-i][c.getLigne()-i] >0 && blanc == false ) || (plateau[c.getColonne()-i][c.getLigne()-i] <0 && blanc ))
            {
                // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
                if(c.getColonne()-i-1 >= 0 && c.getLigne()-i-1 >= 0)
                {
                    if(plateau[c.getColonne()-i-1][c.getLigne()-i-1]  == 0)
                    {
                        // la prise est obligatoire donc les cases qu'on a sauvegardé avant ne sont pas valable (on l'indique avec le boolean)
                        priseDiagonalHG = true;
                        diagonalHG.clear();
                        diagonalHG.push_back(Case(c.getColonne()-i-1 ,c.getLigne()-i-1));
                        //i++;
                        break;
                    }
                    else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                    {
                        break;
                    }
                    
                }
            }

            
            
        }
        
        
    }

    ///// ------------ Diagonal en haut à droite  ----------------- //////////
    
    int longueurDiagonalHD ;
    std::vector<Case> diagonalHD;
    bool priseDiagonalHD = false; // si il y a une prise qui est possible sur la diagonal, il ne faut pas mettre les cases avant la prise (diagonalHG) comme cases dispo

    if(9-c.getColonne() <= c.getLigne())
    {
        longueurDiagonalHD = 9-c.getColonne();
    }
    else
    {
        longueurDiagonalHD = c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalHD ; i++)
    {
        // on regarde si la case est libre
        if(plateau[c.getColonne()+i][c.getLigne()-i] == 0)
        {
            diagonalHD.push_back(Case(c.getColonne()+i ,c.getLigne()-i));
        }
        else
        {
            // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
            if((plateau[c.getColonne()+i][c.getLigne()-i] >0 && blanc ) || (plateau[c.getColonne()+i][c.getLigne()-i] <0 && blanc == false))
            {
                break; // les cases dispo pour cette diagonal s'arréte là
            }
            
            //on regarde si il y a une pièce adverse
            if((plateau[c.getColonne()+i][c.getLigne()-i] >0 && blanc == false ) || (plateau[c.getColonne()+i][c.getLigne()-i] <0 && blanc ))
            {
                // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
                if(c.getColonne()+i+1 <= 9 && c.getLigne()-i-1 >= 0)
                {
                    if(plateau[c.getColonne()+i+1][c.getLigne()-i-1]  == 0)
                    {
                        // la prise est obligatoire donc les cases qu'on a sauvegardé avant ne sont pas valable (on l'indique avec le boolean)
                        priseDiagonalHD = true;
                        diagonalHD.clear();
                        diagonalHD.push_back(Case(c.getColonne()+i+1 ,c.getLigne()-i-1));
                        //i++;
                        break;
                    }
                    else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                    {
                        break;
                    }
                }
                
            }
         
        }
        
        
    }

    ///// ------------ Diagonal en bas à droite  ----------------- //////////
    
    int longueurDiagonalBD ;
    std::vector<Case> diagonalBD;
    bool priseDiagonalBD = false; // si il y a une prise qui est possible sur la diagonal, il ne faut pas mettre les cases avant la prise (diagonalHG) comme cases dispo

    if(9-c.getColonne() <= 9-c.getLigne())
    {
        longueurDiagonalBD = 9-c.getColonne();
    }
    else
    {
        longueurDiagonalBD = 9-c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalBD ; i++)
    {
        // on regarde si la case est libre
        if(plateau[c.getColonne()+i][c.getLigne()+i] == 0)
        {
            diagonalBD.push_back(Case(c.getColonne()+i ,c.getLigne()+i));
        }
        else
        {
            // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
            if((plateau[c.getColonne()+i][c.getLigne()+i] >0 && blanc ) || (plateau[c.getColonne()+i][c.getLigne()+i] <0 && blanc == false))
            {
                break; // les cases dispo pour cette diagonal s'arréte là
            }
            
            //on regarde si il y a une pièce adverse
            if((plateau[c.getColonne()+i][c.getLigne()+i] >0 && blanc == false ) || (plateau[c.getColonne()+i][c.getLigne()+i] <0 && blanc ))
            {
                // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
                if(c.getColonne()+i+1 <= 9 && c.getLigne()+i+1 <= 9)
                {
                    if(plateau[c.getColonne()+i+1][c.getLigne()+i+1]  == 0)
                    {
                        // la prise est obligatoire donc les cases qu'on a sauvegardé avant ne sont pas valable (on l'indique avec le boolean)
                        priseDiagonalBD = true;
                        diagonalBD.clear();
                        diagonalBD.push_back(Case(c.getColonne()+i+1 ,c.getLigne()+i+1));
                        //i++;
                        break;
                    }
                    else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                    {
                        break;
                    }
                }
            }
         
        }
        
        
    }

    ///// ------------ Diagonal en bas à gauche  ----------------- //////////
    
    int longueurDiagonalBG ;
    std::vector<Case> diagonalBG;
    bool priseDiagonalBG = false; // si il y a une prise qui est possible sur la diagonal, il ne faut pas mettre les cases avant la prise (diagonalHG) comme cases dispo

    if(c.getColonne() <= 9-c.getLigne())
    {
        longueurDiagonalBG = c.getColonne();
    }
    else
    {
        longueurDiagonalBG = 9-c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalBG ; i++)
    {
        // on regarde si la case est libre
        if(plateau[c.getColonne()-i][c.getLigne()+i] == 0)
        {
            diagonalBG.push_back(Case(c.getColonne()-i ,c.getLigne()+i));
        }
        else
        {
            // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
            if((plateau[c.getColonne()-i][c.getLigne()+i] >0 && blanc ) || (plateau[c.getColonne()-i][c.getLigne()+i] <0 && blanc == false))
            {
                break; // les cases dispo pour cette diagonal s'arréte là
            }
            
            //on regarde si il y a une pièce adverse
            if((plateau[c.getColonne()-i][c.getLigne()+i] >0 && blanc == false ) || (plateau[c.getColonne()-i][c.getLigne()+i] <0 && blanc ))
            {
                // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
                if(c.getColonne()-i-1 >= 0 && c.getLigne()+i+1 <= 9)
                {
                    if(plateau[c.getColonne()-i-1][c.getLigne()+i+1]  == 0)
                    {
                        // la prise est obligatoire donc les cases qu'on a sauvegardé avant ne sont pas valable (on l'indique avec le boolean)
                        priseDiagonalBG = true;
                        diagonalBG.clear();
                        diagonalBG.push_back(Case(c.getColonne()-i-1 ,c.getLigne()+i+1));
                        //i++;
                        break;
                    }
                    else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                    {
                        break;
                    }
                }
            }
         
        }
        
        
    }

    ///// ------------ fusion des quatres diagonals  ----------------- //////////
    // dans la fusion la prise majoritaire n'est pas prise en compte nn plus
    // on va prendre en compte quand même le fait que la prise est obligatoire

    std::vector<Case> listCase;

    if(priseDiagonalBD || priseDiagonalBG || priseDiagonalHD || priseDiagonalHG)
    {
        if(priseDiagonalBD)
        {
            listCase.insert(listCase.end(),diagonalBD.begin(),diagonalBD.end());
        }
        if(priseDiagonalBG)
        {
            listCase.insert(listCase.end(),diagonalBG.begin(),diagonalBG.end());
        }
        if(priseDiagonalHD)
        {
            listCase.insert(listCase.end(),diagonalHD.begin(),diagonalHD.end());
        }
        if(priseDiagonalHG)
        {
            listCase.insert(listCase.end(),diagonalHG.begin(),diagonalHG.end());
        }
    }
    else
    {
        listCase.insert(listCase.end(),diagonalHG.begin(),diagonalHG.end());
        listCase.insert(listCase.end(),diagonalHD.begin(),diagonalHD.end());
        listCase.insert(listCase.end(),diagonalBD.begin(),diagonalBD.end());
        listCase.insert(listCase.end(),diagonalBG.begin(),diagonalBG.end());
    }
    
    

    

    return listCase;
}

std::vector<Case> Dame::deplacementPrisePossible (std::vector<std::vector<int>> p)
{
    std::vector<std::vector<int>> plateau = p;//p.getPlateau();

    ///// ------------ Diagonal en haut à gauche  ----------------- //////////

    int longueurDiagonalHG ;
    std::vector<Case> diagonalHG;

    if(c.getColonne() <= c.getLigne())
    {
        longueurDiagonalHG = c.getColonne();
    }
    else
    {
        longueurDiagonalHG = c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalHG ; i++)
    {
        
        
        // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
        if((plateau[c.getColonne()-i][c.getLigne()-i] >0 && blanc ) || (plateau[c.getColonne()-i][c.getLigne()-i] <0 && blanc == false))
        {
            break; // les cases dispo pour cette diagonal s'arréte là
        }
        
        //on regarde si il y a une pièce adverse
        if((plateau[c.getColonne()-i][c.getLigne()-i] >0 && blanc == false ) || (plateau[c.getColonne()-i][c.getLigne()-i] <0 && blanc ))
        {
            // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
            if(c.getColonne()-i-1 >= 0 && c.getLigne()-i-1 >= 0)
            {
                if(plateau[c.getColonne()-i-1][c.getLigne()-i-1]  == 0)
                {
                   
                    diagonalHG.clear();
                    diagonalHG.push_back(Case(c.getColonne()-i-1 ,c.getLigne()-i-1));
                    //i++;
                    break;
                }
                else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                {
                    break;
                }
            }
        }
       
    }

    ///// ------------ Diagonal en haut à droite  ----------------- //////////
    
    int longueurDiagonalHD ;
    std::vector<Case> diagonalHD;

    if(9-c.getColonne() <= c.getLigne())
    {
        longueurDiagonalHD = 9-c.getColonne();
    }
    else
    {
        longueurDiagonalHD = c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalHD ; i++)
    {
        
        // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
        if((plateau[c.getColonne()+i][c.getLigne()-i] >0 && blanc ) || (plateau[c.getColonne()+i][c.getLigne()-i] <0 && blanc == false))
        {
            break; // les cases dispo pour cette diagonal s'arréte là
        }
        
        //on regarde si il y a une pièce adverse
        if((plateau[c.getColonne()+i][c.getLigne()-i] >0 && blanc == false ) || (plateau[c.getColonne()+i][c.getLigne()-i] <0 && blanc ))
        {
            // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
            if(c.getColonne()+i+1 <= 9 && c.getLigne()-i-1 >= 0)
            {
                if(plateau[c.getColonne()+i+1][c.getLigne()-i-1]  == 0)
                {
                    diagonalHD.clear();
                    diagonalHD.push_back(Case(c.getColonne()+i+1 ,c.getLigne()-i-1));
                    //i++;
                    break;
                }
                else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                {
                    break;
                }
            }
        } 
        
    }

    ///// ------------ Diagonal en bas à droite  ----------------- //////////
    
    int longueurDiagonalBD ;
    std::vector<Case> diagonalBD;

    if(9-c.getColonne() <= 9-c.getLigne())
    {
        longueurDiagonalBD = 9-c.getColonne();
    }
    else
    {
        longueurDiagonalBD = 9-c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalBD ; i++)
    {

        
        // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
        if((plateau[c.getColonne()+i][c.getLigne()+i] >0 && blanc ) || (plateau[c.getColonne()+i][c.getLigne()+i] <0 && blanc == false))
        {
            break; // les cases dispo pour cette diagonal s'arréte là
        }
        
        //on regarde si il y a une pièce adverse
        if((plateau[c.getColonne()+i][c.getLigne()+i] >0 && blanc == false ) || (plateau[c.getColonne()+i][c.getLigne()+i] <0 && blanc ))
        {
            // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
            if(c.getColonne()+i+1 <= 9 && c.getLigne()+i+1 <= 9)
            {
                if(plateau[c.getColonne()+i+1][c.getLigne()+i+1]  == 0)
                {
                    diagonalBD.clear();
                    diagonalBD.push_back(Case(c.getColonne()+i+1 ,c.getLigne()+i+1));
                    //i++;
                    break;
                }
                else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                {
                    break;
                }
            }
        }
    }

    ///// ------------ Diagonal en bas à gauche  ----------------- //////////
    
    int longueurDiagonalBG ;
    std::vector<Case> diagonalBG;

    if(c.getColonne() <= 9-c.getLigne())
    {
        longueurDiagonalBG = c.getColonne();
    }
    else
    {
        longueurDiagonalBG = 9-c.getLigne();
    }

    for(int i = 1; i <= longueurDiagonalBG ; i++)
    {
        // on regarde si il y une pièce de notre couleur qui nous bloque la diagonal
        if((plateau[c.getColonne()-i][c.getLigne()+i] >0 && blanc ) || (plateau[c.getColonne()-i][c.getLigne()+i] <0 && blanc == false))
        {
            break; // les cases dispo pour cette diagonal s'arréte là
        }
        
        //on regarde si il y a une pièce adverse
        if((plateau[c.getColonne()-i][c.getLigne()+i] >0 && blanc == false ) || (plateau[c.getColonne()-i][c.getLigne()+i] <0 && blanc ))
        {
            // on vérifie qu'il y a une case dispo derrière (les deux prochains if)
            if(c.getColonne()-i-1 >= 0 && c.getLigne()+i+1 <= 9)
            {
                if(plateau[c.getColonne()-i-1][c.getLigne()+i+1]  == 0)
                {
                    diagonalBG.clear();
                    diagonalBG.push_back(Case(c.getColonne()-i-1 ,c.getLigne()+i+1));
                    //i++;
                    break;
                }
                else // il n'y pas de cases dispo derrière , donc le reste de la diagonal est bloqué
                {
                    break;
                }
            }
        }
        
    }

    std::vector<Case> listCase;

    listCase.insert(listCase.end(),diagonalHG.begin(),diagonalHG.end());
    listCase.insert(listCase.end(),diagonalHD.begin(),diagonalHD.end());
    listCase.insert(listCase.end(),diagonalBD.begin(),diagonalBD.end());
    listCase.insert(listCase.end(),diagonalBG.begin(),diagonalBG.end());

    return listCase;
}
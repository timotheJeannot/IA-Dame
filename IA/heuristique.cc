#include "heuristique.h"

int heuristique1(Plateau p,int couleur){
    int valuePieces = 0;
    int valuesPositions = 0;
    int valuePiecesA = 0;
    int valuesPositionsA = 0;
    std::vector<std::vector<int>> plateau = p.getPlateau();

    for(int i =0 ; i<10 ; i++)
    {
        for(int j =0 ; j<10; j++)
        {
            if(plateau[i][j] == couleur)
            {
                valuePieces += 1;
                valuesPositions += plateauPositions[i][j];
            }
            if(plateau[i][j] == couleur*2)
            {
                valuePieces =+ 3;
                valuesPositions += plateauPositions[i][j];
            }
            if(plateau[i][j] == couleur*-1)
            {
                valuePiecesA += 1;
                valuesPositionsA += plateauPositions[i][j];
            }
            if(plateau[i][j] == couleur*-2)
            {
                valuePiecesA =+ 3;
                valuesPositionsA += plateauPositions[i][j];
            }
        }
    }
    return valuePieces *200 - valuePiecesA *200 + valuesPositions - valuesPositionsA;
}
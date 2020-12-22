#include "heuristique.h"

int heuristique1(Plateau p){
    int valuePiecesB = 0;
    int valuesPositionsB = 0;
    int valuePiecesN = 0;
    int valuesPositionsN = 0;
    std::vector<std::vector<int>> plateau = p.getPlateau();

    for(int i =0 ; i<10 ; i++)
    {
        for(int j =0 ; j<10; j++)
        {
            if(plateau[i][j] == 1)
            {
                valuePiecesB += 1;
                valuesPositionsB += plateauPositions[i][j];
            }
            if(plateau[i][j] == 2)
            {
                valuePiecesB =+ 3;
                valuesPositionsB += plateauPositions[i][j];
            }
            if(plateau[i][j] == -1)
            {
                valuePiecesN += 1;
                valuesPositionsN += plateauPositions[i][j];
            }
            if(plateau[i][j] == -2)
            {
                valuePiecesN =+ 3;
                valuesPositionsN += plateauPositions[i][j];
            }
        }
    }
    return valuePiecesB *200 - valuePiecesN *200 + valuesPositionsB - valuesPositionsN;
}
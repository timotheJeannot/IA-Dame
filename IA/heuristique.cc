#include "heuristique.h"

double heuristique1(Plateau p, double vNbPieceScore, double vPosPieceScore){
    double valuePiecesB = 0;
    double valuesPositionsB = 0;
    double valuePiecesN = 0;
    double valuesPositionsN = 0;
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
    return  valuePiecesB *vNbPieceScore - valuePiecesN *vNbPieceScore + valuesPositionsB * vPosPieceScore - valuesPositionsN * vPosPieceScore;
}
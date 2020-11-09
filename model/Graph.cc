//
// Created by ubuntu on 02/11/2020.
//

#include "Graph.h"



void Graph::printStartPiece(){
    renderer.clear();
    printBoard();
    for(int j=0;j<4;j++) {
        for (int i = 0; i < 9; i += 2) {
            if (j % 2 == 0) {
                GPiece(gf::Vector2f(begin.height + ((i + 1) * sizeSquare), begin.col + (j * sizeSquare)), sizeCircle,
                      gf::Color::Black).render(renderer);
            } else {
                GPiece(gf::Vector2f(begin.height + (i * sizeSquare), begin.col + (j * sizeSquare)), sizeCircle, gf::Color::Black).render(
                        renderer);
            }
        }
    }
    for(int j=6;j<10;j++) {
        for (int i = 0; i < 9; i += 2) {
            if (j%2==0 ){
                GPiece(gf::Vector2f(begin.height + (i * sizeSquare), begin.col + (j * sizeSquare)), sizeCircle, gf::Color::White).render(renderer);
            }else{
                GPiece(gf::Vector2f(begin.height + ((i+1) * sizeSquare), begin.col + (j * sizeSquare)), sizeCircle, gf::Color::White).render(renderer);
            }
        }
    }
    renderer.display();
}

void Graph::printBoard(){
    gf::Color4f peru = gf::Color::fromRgba32(205,133,63);
    gf::Color4f saddlebrown = gf::Color::fromRgba32(139,69,19);
    renderer.clear();
    for(int j=0;j<10;j++) {
        for (int i = 0; i < 9; i+=2) {
            if (j%2==0) {
                GSquare(gf::Vector2f(begin.height + (i * sizeSquare), begin.col + (j * sizeSquare)), sizeSquare, peru).render(renderer);
                GSquare(gf::Vector2f(begin.height + ((i + 1) * sizeSquare), begin.col + (j * sizeSquare)), sizeSquare,
                       saddlebrown).render(renderer);
            }else{
                GSquare(gf::Vector2f(begin.height + (i * sizeSquare), begin.col + (j * sizeSquare)), sizeSquare, saddlebrown).render(renderer);
                GSquare(gf::Vector2f(begin.height + ((i + 1) * sizeSquare), begin.col + (j * sizeSquare)), sizeSquare,
                       peru).render(renderer);
            }
        }
    }
    renderer.display();

}

Graph::Graph() : ScreenSize(1000, 1000)
                    , sizeCircle(10)
                    , sizeSquare(50.0f)
                    , begin(300.0f, 300.0f)
                    , window("Jeu de Dame",ScreenSize)
                    , renderer(window)
                    {}

Graph::Graph(gf::Vector2u SSize, const string& gName, gf::Vector2f begin, int sizeC, float sizeS) : ScreenSize(SSize)
        , sizeCircle(sizeC)
        , sizeSquare(sizeS)
        , begin(begin)
        , window(gName,SSize)
        , renderer(window)
        {}



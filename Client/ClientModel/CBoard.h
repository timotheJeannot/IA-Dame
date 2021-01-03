//
// Created by ubuntu on 02/11/2020.
//

#ifndef TEST_GF_CBOARD_H
#define TEST_GF_CBOARD_H

#include <gf/Clock.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Entity.h>
#include <gf/Action.h>
#include <gf/Views.h>
#include <gf/ViewContainer.h>
#include <gf/RenderWindow.h>
#include <gf/EntityContainer.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <gf/Window.h>
#include "../../protocole/protocole.h"
#include "CPiece.h"
#include "CCase.h"
#include "../../model/Plateau.h"

using namespace std;

struct cmpByVector2i {
    bool operator()(const gf::Vector2i& a, const gf::Vector2i& b) const {
        if((a.x == b.x)){
            return(a.y < b.y);
        }
        return(a.x < b.x);
    }
};


class CBoard {
private:

    gf::Vector2f beginBoard;
    int sizeCircle;
    float sizeSquare;
    int myColor = 1;

public:


    // Plateau
    Plateau board;
    gf::Vector2u ScreenSize;
    gf::Window window;
    gf::RenderWindow renderer;

    // entities
    gf::EntityContainer MainEntity;
    std::vector<CPiece>  cPieceBlack;
    std::vector<CPiece>  cPieceWhite;
    std::map<gf::Vector2i, CCase, cmpByVector2i> cCase;

    //action
    gf::LockedView mainView;
    gf::ScreenView screenView;
    gf::ViewContainer views;

    // method
    CBoard(gf::Vector2u SSize, const string& gName, int mycolor);
    CBoard(gf::Vector2u SSize, const string& gName, gf::Vector2f begin, int sizeC, float sizeS);



    void printBoard();
//    void printMovePiece(const Plateau& board, const TCoupReq& req);
    void initBoard();

    int pieceSelect(gf::Vector2i vector);
    //gf::Vector4i doProcessEvent(gf::Event &event, int coul, const std::vector<std::vector<int>>& board);

    void print();

    gf::Vector4i doProcessEvent(gf::Event event, CPiece &vector1, int &index, bool &b, bool &b1);

    gf::Vector2i caseSelect(gf::Vector2i vector);

    void UpdatePiece(gf::Vector2i vector, gf::Vector2i vector2, int index);

    bool CaseVide(gf::Vector2i vector);

    int getSizeCircle() const;

    void setSizeCircle(int sizeCircle);

    float getSizeSquare() const;

    void setSizeSquare(float sizeSquare);

    int getMyColor() const;

    void setMyColor(int myColor);

    bool isInBoard(gf::Vector2i vector);

    void Update(gf::Time time);

    CPiece searchPiece(int index);

    void highlightCase(gf::Vector2i pos);

    void deHighlightCase(gf::Vector2i pos);

    bool isPLayable(gf::Vector2i pos);

    void UpdateMultiPiece(gf::Vector2f vector, int &index);

    void printMovePiece(const TCoupReq &req);

    void UpdatePieceADV(gf::Vector2i vector, gf::Vector2i vector2, int index);

    int pieceSelectADV(gf::Vector2i vector);

    bool isPLayable(gf::Vector2i pos, gf::Vector2i posToGo);
};







#endif //TEST_GF_CBOARD_H

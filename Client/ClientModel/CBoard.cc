//
// Created by ubuntu on 02/11/2020.
//

#include "CBoard.h"
#include "CCase.h"
#include "CPiece.h"


#include <utility>
#include <iostream>

void CBoard::printMovePiece(const TCoupReq& req) {
    std::vector<TCase> deplacementsAdv = req.deplacements;
    TCase posPionAvAdv = req.posPionAv;
    int xAdv = posPionAvAdv.c;
    int yAdv = posPionAvAdv.l;
    gf::Vector2i posAdv(xAdv, yAdv);
    Pion pAdv;
    Dame dAdv ;
    bool col;
    if(myColor==1){
        col= false;
    }else{
        col = true;
    }
    cCase.at(posAdv);
    int size = deplacementsAdv.size();
    if(req.pion.typePion == TTypePion::DAME)
    {
        for(int i = 0 ; i <size; i++)
        {
            TCase cnextAdv = deplacementsAdv[i];
            int x2Adv = cnextAdv.c;
            int y2Adv = cnextAdv.l;
            dAdv = Dame(xAdv,yAdv,col);
            Case cibleAdv(x2Adv,y2Adv);
            board.modifPlateauDeplacementNormal(dAdv,cibleAdv); // ce n'est pas grave si on ne différencie pas les deux types de déplacements, car le serveur à valider le coup
            dAdv.setCase(cibleAdv);

        }
    }
    else
    {
        for(int i = 0 ; i <size; i++)
        {
            TCase cnextAdv = deplacementsAdv[i];
            int x2Adv = cnextAdv.c;
            int y2Adv = cnextAdv.l;
            pAdv = Pion(xAdv,yAdv,col);
            Case cibleAdv(x2Adv,y2Adv);
            board.modifPlateauDeplacementNormal(pAdv,cibleAdv); // ce n'est pas grave si on ne différencies pas les deux types de déplacements, car le serveur à valider le coup
            pAdv.setCase(cibleAdv);
        }
    }



}

void CBoard::initBoard(){
    ScreenSize = gf::Vector2u(1000, 1000);
    sizeCircle = 10;
    sizeSquare = 50.0f;
    beginBoard = gf::Vector2f(250.0f, 250.0f);
    gf::Vector2f boardSize(sizeSquare * 10.0f, sizeSquare * 10.0f);


    gf::ExtendView mainView(ScreenSize/2, boardSize);
    views.addView(mainView);
    views.setInitialFramebufferSize(ScreenSize);


    gf::Color4f peru = gf::Color::fromRgba32(205,133,63);
    gf::Color4f saddlebrown = gf::Color::fromRgba32(139,69,19);
    for(int j=0;j<10;j++) {
        for (int i = 0; i < 10; i++) {
            switch (board.getPlateau()[j][i]) {
                case -1 : {
                    CPiece piece(gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)), sizeCircle,
                                 gf::Color::Black);
                    cPieceBlack.push_back( piece);
                }break;
                case 1 : {
                    CPiece piece(gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)), sizeCircle, gf::Color::White);
                    cPieceWhite.push_back( piece);

                }break;

            }
            if(j%2==0) {
                if(i%2==0){
                    CCase c(gf::Vector2f(beginBoard.height + (j * sizeSquare), beginBoard.col + (i * sizeSquare)),
                            sizeSquare, peru);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));

                }else{
                    CCase c(gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)), sizeSquare, saddlebrown);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));

                }

            }else{
                if(i%2==0) {
                    CCase c(
                            gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)),
                            sizeSquare, saddlebrown);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));
                }else{
                    CCase c(gf::Vector2f(beginBoard.height + (j * sizeSquare), beginBoard.col + ((i) * sizeSquare)), sizeSquare, peru);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));
                }

            }

        }
    }

}

CBoard::CBoard(gf::Vector2u SSize, const string& gName, gf::Vector2f begin, int sizeC, float sizeS) : ScreenSize(SSize)
        , sizeCircle(sizeC)
        , sizeSquare(sizeS)
        , beginBoard(begin)
        , window(gName, SSize)
        , renderer(window)
        {
            initBoard();
        }

CBoard::CBoard(gf::Vector2u SSize, const string& gName): window(gName, SSize),
                                                         renderer(window),
                                                         board(){

    initBoard();

}

void CBoard::printBoard() {
    for(auto & it : cCase){
        it.second.render(renderer);
        if(board.getPlateau()[it.first.x][it.first.y] == 3 ){
            cPieceWhite.at(pieceSelect(it.second.getMPosition())).kill();
            board.setNbPiecesB(board.getNbPiecesB()-1);
        }
        if(board.getPlateau()[it.first.x][it.first.y] == -3 ){
            cPieceBlack.at(pieceSelect(it.second.getMPosition())).kill();
            board.setNbPiecesN(board.getNbPiecesN()-1);
        }

    }
    board.enleverPiecesRafle();

}

void CBoard::print() {
    renderer.clear();
    printBoard();

    for(auto & it : cPieceWhite){
        it.render(renderer);
    }
    for(auto & it : cPieceBlack){
        it.render(renderer);
    }
    renderer.display();
}
gf::Vector2i CBoard::caseSelect(gf::Vector2i vector) {
    for(auto  it : cCase) {
        if (it.second.isCaseSelect(vector)) {

            return it.first;
        }
    }
    return gf::Vector2i(-1,-1);
}
int CBoard::pieceSelect(gf::Vector2i vector) {
    gf::Vector2f caseSel = cCase.at(caseSelect(vector)).getMPosition();
    switch(myColor){
        case 1 :
                for(int i=0;i<cPieceWhite.size();i++){
                    if(cPieceWhite[i].getMPosition() == caseSel){
                        return i;
                    }

                }break;
        case -1 :
                for(int i=0;i<cPieceBlack.size();i++){
                    if(cPieceBlack[i].getMPosition() == caseSel){
                        return i;
                    }
                }break;

    }
    return -1;

}
void CBoard::UpdatePiece(gf::Vector2i vector,  gf::Vector2i vector2, int index) {


    bool caseSelVide = CaseVide(vector);
    int retmodif=0;
    if(caseSelVide){
        Case caseUpdate(vector.x,vector.y);
        Case caseOrigin(vector2.x,vector2.y);
        switch(myColor){
            case -1 :
                /*if(cPieceBlack.at(index).getType()==CPION){
                    Pion pion(caseOrigin,true);
                    board.modifPlateauDeplacementNormal(pion, caseUpdate);

                }else{
                    Dame dame(caseOrigin,true);
                    board.modifPlateauDeplacementNormal(dame, caseUpdate);
                }*/
                cPieceBlack.at(index).setMPosition(vector);break;
            case 1 :
                /*if(cPieceWhite.at(index).getType()==CPION){
                    Pion pion(caseOrigin,false);
                    board.modifPlateauDeplacementNormal(pion, caseUpdate);

                }else{
                    Dame dame(caseOrigin,false);
                    board.modifPlateauDeplacementNormal(dame, caseUpdate);
                }*/
                cPieceWhite.at(index).setMPosition(vector);break;

        }
    }

}
bool CBoard::CaseVide(gf::Vector2i vector) {

    gf::Vector2f caseSel = cCase.at(caseSelect(vector)).getMPosition();
    for(const auto& it : cPieceWhite){
        if(caseSel == it.getMPosition()){
            return false;
        }
    }
    for(const auto& it : cPieceBlack){
        if(caseSel == it.getMPosition()){
            return false;
        }
    }
    return true;

}
gf::Vector4i CBoard::doProcessEvent(gf::Event event, CPiece &vector1, int &index, bool &b, bool &b1) {

    //if (actions.getAction("Select").isActive()) {
        gf::Vector2i mouseCoords = event.mouseButton.coords;
        cout<<"Test1"<<endl;
        if(isInBoard(mouseCoords)) {
            cout<<"Test2"<<endl;
            bool emptySelection = CaseVide(mouseCoords);
            cout<<"Test3"<<endl;
            //s'il a selectionner une piece
            if (b) {
                cout<<"Test4"<<endl;
                if(!emptySelection) {
                    cout<<"Test5"<<endl;
                    int iPieceSel = pieceSelect(mouseCoords);
                    cout<<"Test6"<<endl;
                    CPiece pieceSel = searchPiece(iPieceSel);
                    CPiece oldPiece = searchPiece(index);
                    //verifie s'il deselectionne la piece
                    if(pieceSel.isNotNull()) {
                        if (pieceSel == oldPiece) {
                            cout << "Test7" << endl;
                            b = false;
                            cCase.at(caseSelect(mouseCoords)).deSelected();
                            deHighlightCase(caseSelect(mouseCoords));
                            //TODO faire une animation pour une piece selectionné
                        }else{
                            cout<<"Test12"<<endl;
                            gf::Vector2i old((int)oldPiece.getMPosition().x,(int)oldPiece.getMPosition().y);
                            cCase.at(caseSelect(old)).deSelected();
                            gf::Vector2i pair = caseSelect(mouseCoords);
                            cCase.at(pair).selected();
                            highlightCase(pair);
                            cout<<"Test13 "<<old.x<<"   "<<old.y<<endl;
                            cout<<"Test14"<<endl;
                            index = pieceSelect(mouseCoords);
                            b=true;
                        }
                    }
                }else{
                    cout<<"Test8"<<endl;

                        gf::Vector2i pair2 = caseSelect(searchPiece(index).getMPosition());
                        if(isPLayable(pair2)) {
                            gf::Vector2i pair = caseSelect(mouseCoords);
                            gf::Vector2f newPos = cCase.at(pair).getMPosition();
                            cout << "Test9" << endl;
                            cCase.at(pair2).deSelected();
                            cout << "Test9.1" << endl;
                            deHighlightCase(pair2);
                            cout << "Test9.2" << endl;
                            UpdatePiece(newPos, pair2, index);
                            cout << "Test9.3" << endl;
                            //UpdateMultiPiece(newPos, index);
                            b = false;
                            b1 = true;
                            cout << "Test10" << endl;
                            return gf::Vector4i(pair.x, pair.y, pair2.x, pair2.y);
                        }
                }
            } else {
                cout<<"Test11"<<endl;
                int pieceS = pieceSelect(mouseCoords);
                if(!emptySelection && pieceS>=0){
                    cout<<"Test12"<<endl;
                    index = pieceSelect(mouseCoords);
                    //gf::Vector2i old((int)vector1.getMPosition().x,(int)vector1.getMPosition().y);
                    gf::Vector2i pair = caseSelect(mouseCoords);
                    cCase.at(pair).selected();
                    cout<<"Test13 "<<pair.x<<"   "<<pair.y<<endl;
                    cout<<"Test14"<<endl;
                    b=true;
                    highlightCase(pair);
                    //cout <<"col : "<<caseSelect(vector1.getMPosition()).first.x<<"   "<<caseSelect(vector1.getMPosition()).first.y<<endl;
                    //TODO faire une animation pour une piece selectionné
                }
            }
        }
        return gf::Vector4i(gf::Zero);
   // }

}

int CBoard::getSizeCircle() const {
    return sizeCircle;
}

void CBoard::setSizeCircle(int sizeCircle) {
    CBoard::sizeCircle = sizeCircle;
}

float CBoard::getSizeSquare() const {
    return sizeSquare;
}

void CBoard::setSizeSquare(float sizeSquare) {
    CBoard::sizeSquare = sizeSquare;
}

int CBoard::getMyColor() const {
    return myColor;
}

void CBoard::setMyColor(int myColor) {
    CBoard::myColor = myColor;
}

bool CBoard::isInBoard(gf::Vector2i vector) {

    int limitBoard = (int)sizeSquare * 10;

    return(beginBoard.x < vector.x && vector.x < (beginBoard.x + limitBoard) && beginBoard.y < vector.y && vector.y < (beginBoard.y + limitBoard));

}

void CBoard::Update(gf::Time time) {
    MainEntity.update(time);
}

CPiece CBoard::searchPiece(int index) {

    if(index < 0){
        return CPiece();
    }else {
        switch (myColor) {
            case 1 :
                return cPieceWhite.at(index);
                break;
            case -1 :
                return cPieceBlack.at(index);
                break;
        }
    }
    return CPiece();
}

void CBoard::highlightCase(gf::Vector2i pos) {

    map<Case, vector<vector<Case>>> highlight;
    if(myColor==1){
        highlight = board.cheminsPiecesJouable(true);
    }else{
        highlight = board.cheminsPiecesJouable(false);
    }
    Case case1(pos.x,pos.y);
    auto it = highlight.find(case1);
    if(it != highlight.end()){
        for(auto &&iterator : it->second){
            for(auto &&iter : iterator){
                gf::Vector2i highlightCases(iter.getColonne(), iter.getLigne());
                cCase.at(highlightCases).selected();
            }
        }
    }

}
void CBoard::deHighlightCase(gf::Vector2i pos) {

    map<Case, vector<vector<Case>>> highlight;
    if(myColor==1){
        highlight = board.cheminsPiecesJouable(true);
    }else{
        highlight = board.cheminsPiecesJouable(false);
    }
    Case case1(pos.x,pos.y);
    auto it = highlight.find(case1);
    if(it != highlight.end()){
        for(auto &&iterator : it->second){
            for(auto &&iter : iterator){
                gf::Vector2i highlightCases(iter.getColonne(), iter.getLigne());
                cCase.at(highlightCases).deSelected();
            }
        }
    }

}
bool CBoard::isPLayable(gf::Vector2i pos){

    map<Case, vector<vector<Case>>> highlight;
    if(myColor==1){
        highlight = board.cheminsPiecesJouable(true);
    }else{
        highlight = board.cheminsPiecesJouable(false);
    }
    Case case1(pos.x,pos.y);
    auto it = highlight.find(case1);
    if(it != highlight.end()){
        return true;
    }else{
        return false;
    }

}

















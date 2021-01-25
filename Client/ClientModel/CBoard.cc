//
// Created by ubuntu on 02/11/2020.
//

#include "CBoard.h"

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


            gf::Vector2i oldCase = cCase.at(gf::Vector2i(xAdv,yAdv)).getMPosition();

            gf::Vector2i newCase = gf::Vector2i(x2Adv,y2Adv);

            int indexP = pieceSelectADV(oldCase);
            UpdatePieceADV(newCase,gf::Vector2i(xAdv,yAdv),indexP);
            renderer.clear();
            print();
            gf::sleep(gf::seconds(2));

            xAdv=x2Adv;
            yAdv=y2Adv;

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



            gf::Vector2i oldCase = cCase.at(gf::Vector2i(xAdv,yAdv)).getMPosition();

            gf::Vector2i newCase = gf::Vector2i(x2Adv,y2Adv);

            int indexP = pieceSelectADV(oldCase);
            UpdatePieceADV(newCase,gf::Vector2i(xAdv,yAdv),indexP);
            renderer.clear();
            print();
            gf::sleep(gf::seconds(2));
            xAdv=x2Adv;
            yAdv=y2Adv;

        }
    }




}

void CBoard::initBoard(){
    ScreenSize = gf::Vector2u(1000, 1000);
    sizeCircle = 10.0f;
    sizeSquare = 50.0f;
    beginBoard = gf::Vector2f(300.0f, 300.0f);
    gf::Vector2f boardSize(sizeSquare * 10.0f, sizeSquare * 10.0f);

    window.setSize(ScreenSize);
    window.setFramerateLimit(60);


    //screenView
    mainView = gf::LockedView(ScreenSize/2, boardSize+50.0f);

    views.addView(mainView);
    views.addView(screenView);
    views.setInitialFramebufferSize(ScreenSize);


    gf::Color4f peru = gf::Color::fromRgba32(205,133,63);
    gf::Color4f saddlebrown = gf::Color::fromRgba32(139,69,19);
    for(int j=0;j<10;j++) {
        for (int i = 0; i < 10; i++) {
            switch (board.getPlateau()[j][i]) {
                case -1 : {
                    CPiece piece(gf::Vector2f(beginBoard.height + ((float)j * sizeSquare), beginBoard.col + ((float)i * sizeSquare)), sizeCircle,
                                 gf::Color::Black, gf::Vector2i(i,j));
                    cPieceBlack.push_back( piece);
                }break;
                case 1 : {
                    CPiece piece(gf::Vector2f(beginBoard.height + ((float)j * sizeSquare), beginBoard.col + ((float)i * sizeSquare)), sizeCircle, gf::Color::White, gf::Vector2i(i, j));
                    cPieceWhite.push_back( piece);
                }break;
            }

            if(j%2==0) {
                if(i%2==0){
                    CCase c(gf::Vector2f(beginBoard.height + ((float)j * sizeSquare), beginBoard.col + ((float)i * sizeSquare)),
                            sizeSquare, peru);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));

                }else{
                    CCase c(gf::Vector2f(beginBoard.height + ((float)j * sizeSquare), beginBoard.col + ((float)i * sizeSquare)),
                            sizeSquare, saddlebrown);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));

                }

            }else{
                if(i%2==0) {
                    CCase c(
                            gf::Vector2f(beginBoard.height + ((float)j * sizeSquare), beginBoard.col + ((float)i * sizeSquare)),
                            sizeSquare, saddlebrown);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));
                }else{
                    CCase c(gf::Vector2f(beginBoard.height + ((float)j * sizeSquare), beginBoard.col + ((float)i * sizeSquare)),
                            sizeSquare, peru);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));
                }

            }

        }
    }

    if(myColor == -1){
        mainView.setRotation(gf::Pi);
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

CBoard::CBoard(gf::Vector2u SSize, const string& gName, int mycolor): window(gName, SSize),
                                                         renderer(window),
                                                         myColor(mycolor),
                                                         board(){

    initBoard();

}

void CBoard::printBoard() {
    for(auto & it : cCase){
        it.second.render(renderer);
        switch (board.getPlateau()[it.first.x][it.first.y]) {
            case -3 : {
                for (auto it2 = cPieceWhite.begin(); it2 != cPieceWhite.end(); ++it2) {
                    if(it2->getMPosition().x==it.second.getMPosition().x && it2->getMPosition().y==it.second.getMPosition().y) {
                        cPieceWhite.erase(it2);
                        break;
                    }
                }
            }
                break;
            case 3 : {
                for (auto it2 = cPieceBlack.begin(); it2 != cPieceBlack.end(); ++it2) {
                    if(it2->getMPosition().x==it.second.getMPosition().x && it2->getMPosition().y==it.second.getMPosition().y) {
                        cPieceBlack.erase(it2);
                        break;
                    }
                }

            }
                break;
        }
    }
    board.enleverPiecesRafle();

}

void CBoard::print() {
    renderer.clear();
    renderer.setView(mainView);
    printBoard();

    for(auto & it : cPieceWhite){
        it.render(renderer);
    }
    for(auto & it : cPieceBlack){
        it.render(renderer);
    }
    renderer.setView(screenView);
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
int CBoard::pieceSelectADV(gf::Vector2i vector) {
    gf::Vector2f caseSel = cCase.at(caseSelect(vector)).getMPosition();
    switch(myColor){
        case 1 :
            for(int i=0;i<cPieceBlack.size();i++){
                if(cPieceBlack[i].getMPosition() == caseSel){
                    return i;
                }

            }break;
        case -1 :
            for(int i=0;i<cPieceWhite.size();i++){
                if(cPieceWhite[i].getMPosition() == caseSel){
                    return i;
                }
            }break;

    }
    return -1;

}
void CBoard::UpdatePiece(gf::Vector2i vector,  gf::Vector2i vector2, int index) {


    //bool caseSelVide = CaseVide(vector);
    int retmodif=0;
    //if(caseSelVide){
        Case caseUpdate(vector.x,vector.y);
        Case caseOrigin(vector2.x,vector2.y);
        switch(myColor){
            case -1 : {

                    CPiece &thePiece = cPieceBlack.at(index);
                    thePiece.setMPosition(cCase.at(vector).getMPosition());
                    if(vector.y == 9 ){
                        thePiece.setType(CDAME);
                    }
                }
                break;
            case 1 :{
                    CPiece &thePiece2 = cPieceWhite.at(index);
                    thePiece2.setMPosition(cCase.at(vector).getMPosition());
                    if(vector.y == 0){
                        thePiece2.setType(CDAME);
                    }
                }
                break;

        }
    //}

}
void CBoard::UpdatePieceADV(gf::Vector2i vector,  gf::Vector2i vector2, int index) {


    //bool caseSelVide = CaseVide(vector);
    int retmodif=0;
    //if(caseSelVide){
        Case caseUpdate(vector.x,vector.y);
        Case caseOrigin(vector2.x,vector2.y);
        switch(myColor){
            case -1 :
            {
                CPiece &thePiece2 = cPieceWhite.at(index);
                thePiece2.setMPosition(cCase.at(vector).getMPosition());
                if(vector.y == 0){
                    thePiece2.setType(CDAME);
                }
            }break;
            case 1 :
            {
                CPiece &thePiece = cPieceBlack.at(index);
                thePiece.setMPosition(cCase.at(vector).getMPosition());
                if(vector.y == 9){
                    thePiece.setType(CDAME);
                }
            }break;
        }
   // }

}
bool CBoard::CaseVide(gf::Vector2i vector) {

    gf::Vector2i index=caseSelect(vector);

    gf::Vector2f caseSel = cCase.at(index).getMPosition();
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
bool CBoard::doProcessEvent(gf::Event event, CPiece &vector1, int &index, bool &isSelectedPiece, gf::Vector4i &MovePiece) {

    if(event.type == gf::EventType::MouseButtonPressed) {
        gf::Vector2i mouseCoords = renderer.mapPixelToCoords(event.mouseButton.coords, mainView);

        if (isInBoard(mouseCoords)) {

            bool emptySelection = CaseVide(mouseCoords);

            //s'il a selectionner une piece
            if (isSelectedPiece) {

                if (!emptySelection) {

                    int iPieceSel = pieceSelect(mouseCoords);

                    CPiece pieceSel = searchPiece(iPieceSel);
                    CPiece oldPiece = searchPiece(index);
                    //verifie s'il deselectionne la piece
                    if (pieceSel.isNotNull()) {
                        if (pieceSel == oldPiece) {

                            isSelectedPiece = false;
                            cCase.at(caseSelect(mouseCoords)).deSelected();
                            deHighlightCase(caseSelect(mouseCoords));
                            //TODO faire une animation pour une piece selectionné
                        } else {

                            gf::Vector2i old((int) oldPiece.getMPosition().x, (int) oldPiece.getMPosition().y);
                            auto oldc = caseSelect(old);
                            cCase.at(oldc).deSelected();
                            deHighlightCase(oldc);
                            gf::Vector2i pair = caseSelect(mouseCoords);
                            cCase.at(pair).selected();
                            highlightCase(pair);

                            index = pieceSelect(mouseCoords);
                            isSelectedPiece = true;
                        }
                    }
                } else {


                    gf::Vector2i pair2 = caseSelect(searchPiece(index).getMPosition());
                    gf::Vector2i pair = caseSelect(mouseCoords);
                    if (isPLayable(pair2, pair)) {

                        cCase.at(pair2).deSelected();

                        deHighlightCase(pair2);

                        vector<Case> lMP = listMovePiece(pair2, pair);
                        gf::Vector2i n2pair = pair2;
                        for (auto it : lMP) {
                            gf::Vector2i npair(it.getColonne(), it.getLigne());
                            UpdatePiece(npair, pair2, index);
                            pair2 = npair;
                            renderer.clear();
                            print();
                            gf::sleep(gf::seconds(2));
                        }

                        //UpdateMultiPiece(newPos, index);
                        isSelectedPiece = false;
                        MovePiece = gf::Vector4i(lMP.front().getColonne(), lMP.front().getLigne(), n2pair.x, n2pair.y);
                        return true;
                    }
                }
            } else {

                if (!emptySelection) {

                    index = pieceSelect(mouseCoords);
                    //gf::Vector2i old((int)vector1.getMPosition().x,(int)vector1.getMPosition().y);
                    if (index >= 0) {
                        gf::Vector2i pair = caseSelect(mouseCoords);
                        cCase.at(pair).selected();

                        isSelectedPiece = true;
                        highlightCase(pair);
                    }
                }
            }
        }
    }
        return false;
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
                if(iter == iterator.back()) {
                    cCase.at(highlightCases).selected();
                }else{
                    cCase.at(highlightCases).selectedGray();
                }
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
bool CBoard::isPLayable(gf::Vector2i pos, gf::Vector2i posToGo){

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
            if(posToGo.x == iterator.back().getColonne() && posToGo.y == iterator.back().getLigne()){
                return true;
            }
        }
    }
    return false;
}
vector<Case> CBoard::listMovePiece(gf::Vector2i pos, gf::Vector2i posToGo){
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
            if(posToGo.x == iterator.back().getColonne() && posToGo.y == iterator.back().getLigne()){
                return iterator;
            }
        }
    }
    return vector<Case>();
}
void CBoard::gloryCase(gf::Vector2i pos){
    map<Case, vector<vector<Case>>> highlight;
    if(myColor==1){
        highlight = board.cheminsPiecesJouable(true);
    }else{
        highlight = board.cheminsPiecesJouable(false);
    }

    for(const auto& iterator : highlight){
        gf::Vector2i highlightCases(iterator.first.getColonne(), iterator.first.getLigne());
        cCase.at(highlightCases).subrillance();
    }
}

















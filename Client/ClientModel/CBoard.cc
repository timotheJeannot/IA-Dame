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

            cout<<xAdv<<"   "<<yAdv<<endl;
            gf::Vector2i oldCase = cCase.at(gf::Vector2i(xAdv,yAdv)).getMPosition();
            cout<<oldCase.x<<"    "<<oldCase.y<<endl;
            gf::Vector2i newCase = gf::Vector2i(x2Adv,y2Adv);
            cout<<newCase.x<<"    "<<newCase.y<<endl;
            cout<<pieceSelectADV(oldCase)<<endl;
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


            cout<<xAdv<<"   "<<yAdv<<endl;
            gf::Vector2i oldCase = cCase.at(gf::Vector2i(xAdv,yAdv)).getMPosition();
            cout<<oldCase.x<<"    "<<oldCase.y<<endl;
            gf::Vector2i newCase = gf::Vector2i(x2Adv,y2Adv);
            cout<<newCase.x<<"    "<<newCase.y<<endl;
            cout<<pieceSelectADV(oldCase)<<endl;
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
    sizeCircle = 10;
    sizeSquare = 50.0f;
    beginBoard = gf::Vector2f(300.0f, 300.0f);
    gf::Vector2f boardSize(sizeSquare * 10.0f, sizeSquare * 10.0f);

    window.setSize(ScreenSize);
    //window.setVerticalSyncEnabled();
    window.setFramerateLimit(60);

    //screenView
    mainView = gf::LockedView(ScreenSize/2, boardSize+50.0f);
    cout<<mainView.getSize().x<<"     "<<screenView.getSize().y<<endl;
    views.addView(mainView);
    views.addView(screenView);
    views.setInitialFramebufferSize(ScreenSize);


    gf::Color4f peru = gf::Color::fromRgba32(205,133,63);
    gf::Color4f saddlebrown = gf::Color::fromRgba32(139,69,19);
    for(int j=0;j<10;j++) {
        for (int i = 0; i < 10; i++) {
            CPiece *pPiece= nullptr;
            switch (board.getPlateau()[j][i]) {
                case -1 : {
                    CPiece piece(gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)), sizeCircle,
                                 gf::Color::Black, gf::Vector2i(i,j));
                    cPieceBlack.push_back( piece);
                    pPiece=&piece;
                }break;
                case 1 : {
                    CPiece piece(gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)), sizeCircle, gf::Color::White, gf::Vector2i(i,j));
                    cPieceWhite.push_back( piece);
                    pPiece=&piece;
                }break;
            }

            if(j%2==0) {
                if(i%2==0){
                    CCase c(gf::Vector2f(beginBoard.height + (j * sizeSquare), beginBoard.col + (i * sizeSquare)),
                            sizeSquare, peru,pPiece);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));

                }else{
                    CCase c(gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)), sizeSquare, saddlebrown,pPiece);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));

                }

            }else{
                if(i%2==0) {
                    CCase c(
                            gf::Vector2f(beginBoard.height + ((j) * sizeSquare), beginBoard.col + (i * sizeSquare)),
                            sizeSquare, saddlebrown,pPiece);
                    cCase.insert(std::pair<gf::Vector2i, CCase>(gf::Vector2i(j, i), c));
                }else{
                    CCase c(gf::Vector2f(beginBoard.height + (j * sizeSquare), beginBoard.col + ((i) * sizeSquare)), sizeSquare, peru,pPiece);
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
                for (std::vector<CPiece>::iterator it2 = cPieceWhite.begin(); it2 != cPieceWhite.end(); ++it2) {
                    if(it2->getMCase().x==it.first.x && it2->getMCase().y==it.first.y) {
                        cPieceWhite.erase(it2);
                        break;
                    }
                }
            }
                break;
            case 3 : {
                for (std::vector<CPiece>::iterator it2 = cPieceBlack.begin(); it2 != cPieceBlack.end(); ++it2) {
                    if(it2->getMCase().x==it.first.x && it2->getMCase().y==it.first.y) {
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
            for(int i=0;i<cPieceWhite.size();i++){
                if(cPieceBlack[i].getMPosition() == caseSel){
                    return i;
                }

            }break;
        case -1 :
            for(int i=0;i<cPieceBlack.size();i++){
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
                    thePiece.setMCase(vector);
                    thePiece.setMPosition(cCase.at(vector).getMPosition());
                    if(vector.y == 9 ){
                        thePiece.setType(CDAME);
                    }
                }
                break;
            case 1 :{
                    CPiece &thePiece2 = cPieceWhite.at(index);
                    thePiece2.setMCase(vector);
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
                thePiece2.setMCase(vector);
                thePiece2.setMPosition(cCase.at(vector).getMPosition());
                if(vector.y == 0){
                    thePiece2.setType(CDAME);
                }
            }break;
            case 1 :
            {
                CPiece &thePiece = cPieceBlack.at(index);
                thePiece.setMCase(vector);
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
    cout<<"case s : "<<index.x<<"               "<<index.y<<endl;
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
        cout << "Test1" << endl;
        if (isInBoard(mouseCoords)) {
            cout << "Test2" << endl;
            bool emptySelection = CaseVide(mouseCoords);
            cout << "Test3" << endl;
            //s'il a selectionner une piece
            if (isSelectedPiece) {
                cout << "Test4" << endl;
                if (!emptySelection) {
                    cout << "Test5" << endl;
                    int iPieceSel = pieceSelect(mouseCoords);
                    cout << "Test6" << endl;
                    CPiece pieceSel = searchPiece(iPieceSel);
                    CPiece oldPiece = searchPiece(index);
                    //verifie s'il deselectionne la piece
                    if (pieceSel.isNotNull()) {
                        if (pieceSel == oldPiece) {
                            cout << "Test7" << endl;
                            isSelectedPiece = false;
                            cCase.at(caseSelect(mouseCoords)).deSelected();
                            deHighlightCase(caseSelect(mouseCoords));
                            //TODO faire une animation pour une piece selectionné
                        } else {
                            cout << "Test12" << endl;
                            gf::Vector2i old((int) oldPiece.getMPosition().x, (int) oldPiece.getMPosition().y);
                            auto oldc = caseSelect(old);
                            cCase.at(oldc).deSelected();
                            deHighlightCase(oldc);
                            gf::Vector2i pair = caseSelect(mouseCoords);
                            cCase.at(pair).selected();
                            highlightCase(pair);
                            cout << "Test13 " << old.x << "   " << old.y << endl;
                            cout << "Test14" << endl;
                            index = pieceSelect(mouseCoords);
                            isSelectedPiece = true;
                        }
                    }
                } else {
                    cout << "Test8" << endl;

                    gf::Vector2i pair2 = caseSelect(searchPiece(index).getMPosition());
                    gf::Vector2i pair = caseSelect(mouseCoords);
                    if (isPLayable(pair2, pair)) {
                        //gf::Vector2f newPos = cCase.at(pair).getMPosition();
                        cout << "Test9" << endl;
                        cCase.at(pair2).deSelected();
                        cout << "Test9.1" << endl;
                        deHighlightCase(pair2);
                        cout << "Test9.2" << endl;
                        vector<Case> lMP = listMovePiece(pair2, pair);
                        gf::Vector2i n2pair = pair2;
                        for (auto it : lMP) {
                            gf::Vector2i npair(it.getColonne(), it.getLigne());
                            UpdatePiece(npair, pair2, index);
                            pair2 = npair;
                        }
                        cout << "Test9.3" << endl;
                        //UpdateMultiPiece(newPos, index);
                        isSelectedPiece = false;
                        cout << "Test10" << endl;
                        cout << lMP.front().getColonne() << "   " << lMP.front().getLigne() << endl;
                        MovePiece = gf::Vector4i(lMP.front().getColonne(), lMP.front().getLigne(), n2pair.x, n2pair.y);
                        return true;
                    }
                }
            } else {
                cout << "Test11" << endl;
                if (!emptySelection) {
                    cout << "Test12" << endl;
                    index = pieceSelect(mouseCoords);
                    //gf::Vector2i old((int)vector1.getMPosition().x,(int)vector1.getMPosition().y);
                    if (index >= 0) {
                        gf::Vector2i pair = caseSelect(mouseCoords);
                        cCase.at(pair).selected();
                        cout << "Test13 " << pair.x << "   " << pair.y << endl;
                        cout << "Test14" << endl;
                        isSelectedPiece = true;
                        highlightCase(pair);
                    }
                    //cout <<"col : "<<caseSelect(vector1.getMPosition()).first.x<<"   "<<caseSelect(vector1.getMPosition()).first.y<<endl;
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
    cout<<"limite board"<<limitBoard<<endl;
    cout<<"limite board x "<<beginBoard.x + limitBoard<<endl;
    cout<<"limite board y "<<beginBoard.y + limitBoard<<endl;
    cout<<"mousecoord x "<<vector.x<<endl;
    cout<<"mousecoord y "<<vector.y<<endl;
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

















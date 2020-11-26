#include <iostream>
#include<cstring>
#include<string>

#include <string>
#include <vector>

#include <gf/TcpSocket.h>
#include <gf/Packet.h>
#include <gf/Id.h>
#include <gf/SerializationOps.h>
#include <gf/Widget.h>
#include "ClientModel/CBoard.h"



#include "clientTools.h"



using namespace gf::literals;
using namespace std;


int main(int argc, char ** argv)
{
    bool myTurn;

    /* verification des arguments */
    if (argc < 4) {
        //printf("usage : %s nom/IPServ port nomJoueur \n", argv[0]);
        cout<<"usage "<<argv[0]<<"% nom/IPServ port nomJoueur \n";
        return -1;
    }

    string ia;
    bool b = false;

    if (argc == 5) {
        ia = argv[4];
        if (ia == "-IA") {
            b = true;
        }

    }

    /************ Initialisation de la communication **********/
    char * serv = argv[1];
    int port = atoi(argv[2]);

    // création de la socket tcp au server avec le bon port
    gf::TcpSocket socket(serv,to_string(port));
    if (!socket) {
        // Handle error
        cerr<<"erreur lors de la création de la socket pour "<<serv<<" avec le port "<<port<<"\n";
        return -1;
    }

    //demande de la couleur au client

    int err = 0;
    TPartieReq req;
    req.idReq = PARTIE;
    //req.nomJoueur = "joueur 1"; // à modifier
    req.nomJoueur = argv[3];
    req.coulPion = 1;

    gf::Packet packet;
    packet.is(req);
    if(gf::SocketStatus::Data != socket.sendPacket(packet))
    {
        cerr<<"erreur lors de l'envoi de demande partie au serveur";
        return -1;
    }


    if( gf::SocketStatus::Data != socket.recvPacket(packet))
    {
        cerr<<"erreur lors de la réception de confirmation de partie du serveur";
        return -1;
    }

    auto repPartie = packet.as<PartieRep>();


    int couleur = initColor(repPartie.validCoulPion, req.coulPion);

    if(couleur == 1){
        myTurn=true;
    }else{
        myTurn=false;
    }

    cout<<"Vous jouez la couleur : "<<couleur<<" \n";

    /************** Début de partie ********************/
    cout<<"test0";
    Plateau plateau;
    cout<<"test1";
    std::string title = "Jeu de dame";
    title += argv[3];
    CBoard board(gf::Vector2i(1000, 1000), title);
    board.setMyColor(couleur);
    gf::Event event;
    gf::Vector4i movePiece = gf::Vector4i(gf::Zero);
    vector<gf::Vector2i> CasePossible;
    CPiece pieceSelected = CPiece();
    bool isSelected=false;
    bool isMoved=false;
    gf::Clock clock;
    int indexP, depl;
    cout<<"boolean selection :"<<isSelected<<endl;

    if(b){
        board.window.setVisible(false);
    }
    gf::ActionContainer actions;

    gf::Action closeWindowAction("Close window");
    closeWindowAction.addCloseControl();
    closeWindowAction.addKeycodeKeyControl(gf::Keycode::Escape);
    actions.addAction(closeWindowAction);

    gf::Action SelectAction("Select");
    SelectAction.addMouseButtonControl(gf::MouseButton::Left);
    SelectAction.setInstantaneous();
    actions.addAction(SelectAction);

    while (board.window.isOpen())
    {
        while(board.window.pollEvent(event)){
            actions.processEvent(event);
        }

        if(actions.getAction("Close window").isActive()){
            board.window.close();
        }

        if(myTurn) // On commence
        {


            if (actions.getAction("Select").isActive() && !b) {
                movePiece = board.doProcessEvent(event, pieceSelected,indexP, isSelected, isMoved);

                cout<<"boolean selection :"<<isSelected<<endl;
                cout<<"PieceSelection :"<<board.cPieceWhite.at(indexP).getMPosition().x<<"   "<<board.cPieceWhite.at(indexP).getMPosition().y<<endl;
                cout<<"PieceSelection :"<<pieceSelected.getMPosition().x<<"   "<<pieceSelected.getMPosition().y<<endl;
                //CasePossible = plateau.modifPlateauDeplacementNormal(pieceSelected, )

            }
            TCoupReq coup;
            if (b) {
                cout<<"test1"<<endl;
                coup = buildCoupAlea(board.board, couleur);
            }else if (isMoved) {
                isMoved = false;
                coup = buildCoup(board.board, couleur, movePiece, err, depl);

                if (err == 1) {
                    cerr << "erreur lors de la création du coup";
                    return -1;
                }

            }
                packet.is(coup);
                if (gf::SocketStatus::Data != socket.sendPacket(packet)) {
                    cerr << "erreur lors de l'envoi de coup";
                    return -1;
                }
            std::cout<<"test 41\n";
            if (gf::SocketStatus::Data != socket.recvPacket(packet)) {
                cerr << "erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }

            std::cout<<"test 42\n";
            auto coupRep = packet.as<TCoupRep>();
            if(coupRep.propCoup == GAGNE)
            {
                cout<<"victoire\n";
                break;
            }
            if(coupRep.propCoup == NUL)
            {
                cout<<"match nul\n";
                break;
            }
            if(coupRep.propCoup == PERDU)
            {
                cout<<"défaite\n";
                break;
            }
            myTurn = false;


            /*
            std::cout<<"test 43\n";

            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            std::cout<<"test 44\n";
            auto coupAdv = packet.as<TCoupReq>();
            std::cout<<"test 45\n";
            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            std::cout<<"test 46\n";
            auto coupAdvRep = packet.as<TCoupRep>();
            std::cout<<"test 47\n";
            if(coupAdvRep.propCoup == CONT)
            {
                if(coupAdvRep.validCoup == VALID)
                {
                    modifCoupAdv(coupAdv, plateau, 1);
                    //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
                    //plateau.printMovePiece();
                }
            }
            else
            {
                // la partie est fini, il faut afficher le résultat
                if(coupAdvRep.propCoup == GAGNE)
                {
                    cout<<"défaite\n";
                }
                if(coupAdvRep.propCoup == NUL)
                {
                    cout<<"match nul\n";
                }
                if(coupAdvRep.propCoup == PERDU)
                {
                    cout<<"victoire\n";
                }
                break;
            }*/

                /*if (gf::SocketStatus::Data != socket.recvPacket(packet)) {
                    cerr << "erreur lors de la réception de confirmation de partie du serveur";
                    return -1;
                }

                auto coupRep = packet.as<TCoupRep>();


                if (coupRep.propCoup == CONT) {
                    if (coupRep.validCoup == VALID) {
                        //modifCoupAdv(coupAdv, plateau, 1);
                        //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
                        //board.print();
                        myTurn=false;

                    }
                } else {

                    if(coupRep.propCoup == GAGNE)
                    {
                        cout<<"victoire\n";
                        break;
                    }
                    if(coupRep.propCoup == NUL)
                    {
                        cout<<"match nul\n";
                        break;
                    }
                    if(coupRep.propCoup == PERDU)
                    {
                        cout<<"défaite\n";
                        break;
                    }
                }

                auto coupAdv = packet.as<TCoupReq>();

                if (gf::SocketStatus::Data != socket.recvPacket(packet)) {
                    cerr << "erreur lors de la réception de confirmation de partie du serveur";
                    return -1;
                }

                auto coupAdvRep = packet.as<TCoupRep>();

                if (coupAdvRep.propCoup == CONT) {
                    if (coupAdvRep.validCoup == VALID) {
                        modifCoupAdv(coupAdv, plateau, 1);
                        //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
                        //board.print();
                        myTurn=true;

                    }
                } else {

                    if(coupAdvRep.propCoup == GAGNE)
                    {
                        cout<<"victoire\n";
                        break;
                    }
                    if(coupAdvRep.propCoup == NUL)
                    {
                        cout<<"match nul\n";
                        break;
                    }
                    if(coupAdvRep.propCoup == PERDU)
                    {
                        cout<<"défaite\n";
                        break;
                    }
                }*/

        }else {
            std::cout<<"test 48\n";
            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur1";
                return -1;
            }
            std::cout<<"test 49\n";
            auto coupAdv = packet.as<TCoupReq>();
            std::cout<<"test 50\n";
            if (gf::SocketStatus::Data != socket.recvPacket(packet)) {
                cerr << "erreur lors de la réception de confirmation de partie du serveur2";
                return -1;
            }
            std::cout<<"test 51\n";
            auto coupAdvRep = packet.as<TCoupRep>();
            std::cout<<"test 52\n";
            if (coupAdvRep.propCoup == CONT) {
                if (coupAdvRep.validCoup == VALID) {
                    if(b){
                        modifCoupAdv(coupAdv, board.board, couleur);
                    }else{
                        board.printMovePiece(coupAdv);
                    }
                    //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
                    //board.printMovePiece(coupAdv);
                    myTurn = true;
                }
            } else {
                if (coupAdvRep.propCoup == GAGNE) {
                    cout << "défaite\n";
                }
                if (coupAdvRep.propCoup == NUL) {
                    cout << "match nul\n";
                }
                if (coupAdvRep.propCoup == PERDU) {
                    cout << "victoire\n";
                }
                break;
            }
            std::cout<<"test 53\n"<<"my_Turn = "<<myTurn<<endl;
        }


        gf::Time time = clock.restart();
        //board.Update(time);

        board.print();

        actions.reset();

    }

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
    return 0;
}
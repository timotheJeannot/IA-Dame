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
#include <gf/Sleep.h>
#include "ClientModel/CBoard.h"
#include "ClientNetwork.h"


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


    /************ Initialisation de la communication **********/
    char * serv = argv[1];
    int port = atoi(argv[2]);

    // création de la socket tcp au server avec le bon port
    //gf::TcpSocket socket(serv,to_string(port));
    ClientNetwork network;
    network.connect(serv,to_string(port));
    gf::sleep(gf::milliseconds(500));
    assert(network.isConnected());
    /*if (!socket) {
        // Handle error
        cerr<<"erreur lors de la création de la socket pour "<<serv<<" avec le port "<<port<<"\n";
        return -1;
    }*/

    //demande de la couleur au client

    int err = 0;
    TPartieReq req;
    req.idReq = PARTIE;
    //req.nomJoueur = "joueur 1"; // à modifier
    req.nomJoueur = argv[3];
    req.coulPion = 1;

    network.send(req);
    gf::Packet packet;
    network.queue.wait(packet);
    assert(packet.getType() == PartieRep::type);

    auto repPartie = packet.as<PartieRep>();


    int couleur = initColor(repPartie.validCoulPion, req.coulPion);

    if(couleur == 1){
        myTurn=true;
    }else{
        myTurn=false;
    }

    cout<<"Vous jouez la couleur : "<<couleur<<" \n";

    /************** Début de partie ********************/
    Plateau plateau;
    std::string title = "Jeu de dame";
    title += argv[3];
    CBoard board(gf::Vector2i(gf::Zero), title,couleur);
    gf::Event event;
    gf::Vector4i movePiece = gf::Vector4i(gf::Zero);
    vector<gf::Vector2i> CasePossible;
    CPiece pieceSelected = CPiece();
    bool isSelected=false;
    bool isMoved=false;
    int cpt = 0;
    gf::Clock clock;
    int indexP, depl=0;

    gf::ActionContainer actions;

    gf::Action closeWindowAction("Close window");
    closeWindowAction.addCloseControl();
    actions.addAction(closeWindowAction);

    gf::Action clickAction("select");
    clickAction.addMouseButtonControl(gf::MouseButton::Left);
    clickAction.setInstantaneous();
    actions.addAction(clickAction);

    while (board.window.isOpen())
    {
        gf::Time time = clock.restart();
        //board.Update(time);

        board.print();

        actions.reset();

        while(board.window.pollEvent(event)){
            actions.processEvent(event);
            board.views.processEvent(event);
        }

        if(closeWindowAction.isActive()){
            board.window.close();
            break;
        }

        if(myTurn) // On commence
        {
            if(clickAction.isActive()) {
                TCoupReq coup;
                if (board.doProcessEvent(event, pieceSelected, indexP, isSelected, movePiece)) {
                    isMoved = false;
                    coup = buildCoup(board.board, couleur, movePiece, err, depl);

                    if (err == 1) {
                        cerr << "erreur lors de la création du coup";
                        return -1;
                    }

                    network.send(coup);

                    network.queue.wait(packet);

                    auto coupRep = packet.as<TCoupRep>();
                    if (coupRep.propCoup == GAGNE) {
                        cout << "victoire\n";
                        break;
                    }
                    if (coupRep.propCoup == NUL) {
                        cout << "match nul\n";
                        break;
                    }
                    if (coupRep.propCoup == PERDU) {
                        cout << "défaite\n";
                        break;
                    }

                    myTurn = false;
                }
            }
        }else {

            if(network.queue.poll(packet)) {
                auto coupAdv = packet.as<TCoupReq>();
                network.queue.wait(packet);
                auto coupAdvRep = packet.as<TCoupRep>();
                if (coupAdvRep.propCoup == CONT) {
                    if (coupAdvRep.validCoup == VALID) {
                        board.printMovePiece(coupAdv);
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
            }
        }

    }

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
    return 0;
}
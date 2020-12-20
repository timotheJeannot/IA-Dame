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


#include "clientTools.h"



using namespace gf::literals;
using namespace std;


int main(int argc, char ** argv)
{
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

    cout<<"Vous jouez la couleur : "<<couleur<<" \n";

    /************** Début de partie ********************/
    Plateau plateau;
    tree* node = new tree;
    node->p = plateau;
    node->value = -2147483648;
    if(couleur == -1)
    {
        node->childs = childs(plateau,1); // on a besoin d'instancier les childs quand on joue en second au premier tours
    }
    while (true)
    {
        //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
        //plateau.graph.printStartPiece();

        if(couleur == 1) // On commence
        {
            int choice;
            TCoupReq coup = buildCoupHeur1(plateau, 1,*node , choice);
            cout<<"alors est on passé ici ? \n";
            node = &(node->childs[choice]);

            packet.is(coup);
            if(gf::SocketStatus::Data != socket.sendPacket(packet))
            {
                cerr<<"erreur lors de l'envoi de coup";
                return -1;
            }
            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            //plateau.printMovePiece();
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



            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            auto coupAdv = packet.as<TCoupReq>();

            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            auto coupAdvRep = packet.as<TCoupRep>();

            if(coupAdvRep.propCoup == CONT)
            {
                if(coupAdvRep.validCoup == VALID)
                {
                    modifCoupAdv(coupAdv, plateau, 1);
                    //on va regarder quel est le le noeud qu'a choisi l'adversaire
                    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                    for(int i =0 ; i<node->childs.size() ; i++)
                    {
                        cout<<node->childs[i].p.afficheTerminal();
                        if(node->childs[i].p == plateau)
                        {
                            cout<<"////////////////////////////////////////////////////////////////////////////////////////////\n";
                            cout<<"test modif du node pour prendre en compte le coup adverse\n";
                            node = &(node->childs[i]);
                            break;
                        }
                    }
                    cout<<" ?????????????????????????????????????????????????????????????????????????????????????????????\n";

                    //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
                    //plateau.printMovePiece();
                }
            }
            else
            {
                /* la partie est fini, il faut afficher le résultat */
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
            }

        }
        else
        {
            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            auto coupAdv = packet.as<TCoupReq>();
            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            auto coupAdvRep = packet.as<TCoupRep>();
            if(coupAdvRep.propCoup == CONT)
            {
                if(coupAdvRep.validCoup == VALID)
                {
                    modifCoupAdv(coupAdv, plateau, -1);
                    //on va regarder quel est le le noeud qu'a choisi l'adversaire
                    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                    for(int i =0 ; i<node->childs.size() ; i++)
                    {
                        cout<<node->childs[i].p.afficheTerminal();
                        if(node->childs[i].p == plateau)
                        {
                            cout<<"////////////////////////////////////////////////////////////////////////////////////////////\n";
                            cout<<"test modif du node pour prendre en compte le coup adverse\n";
                            node = &(node->childs[i]);
                            break;
                        }
                    }
                    cout<<" ?????????????????????????????????????????????????????????????????????????????????????????????\n";

                    //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
                    //plateau.printMovePiece();
                }
            }
            else
            {
                /* la partie est fini, il faut afficher le résultat */
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
            }
            int choice;
            TCoupReq coup = buildCoupHeur1(plateau,-1,*node , choice);
            cout<<"alors est on passé ici ? \n";
            node = &(node->childs[choice]);
            cout<<"et maintenant ?\n";

            packet.is(coup);
            if(gf::SocketStatus::Data != socket.sendPacket(packet))
            {
                cerr<<"erreur lors de l'envoi de coup";
                return -1;
            }
            if( gf::SocketStatus::Data != socket.recvPacket(packet))
            {
                cerr<<"erreur lors de la réception de confirmation de partie du serveur";
                return -1;
            }
            //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            //plateau.printMovePiece();
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

        }
        cout<<plateau.afficheTerminal();

    }

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
    return 0;
}
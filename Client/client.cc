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
    if (argc != 4) {
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
    
    while (true)
    {
        //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
        //plateau.graph.printStartPiece();


        if(couleur == 1) // On commence
        {
            TCoupReq coup = buildCoup(plateau, 1, err);
            if (err == 1) {
                cerr<<"erreur lors de la création du coup";
                return -1;
            }

          packet.is(coup);
          if(gf::SocketStatus::Data != socket.sendPacket(packet))
          {
              cerr<<"erreur lors de l'envoi de coup";
              return -1;
          }
          std::cout<<"testC0\n";
          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              return -1;
          }
          std::cout<<"testC1\n";
          //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            //plateau.printMovePiece();
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
            std::cout<<"test 48\n";
          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              return -1;
          }
            std::cout<<"test 49\n";
          auto coupAdv = packet.as<TCoupReq>();
            std::cout<<"test 50\n";
          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              return -1;
          }
            std::cout<<"test 51\n";
          auto coupAdvRep = packet.as<TCoupRep>();
            std::cout<<"test 52\n";
          if(coupAdvRep.propCoup == CONT)
          {
            if(coupAdvRep.validCoup == VALID)
            {
                modifCoupAdv(coupAdv, plateau, -1);
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
            std::cout<<"test 53\n";
          TCoupReq coup = buildCoup(plateau, -1, err);
            std::cout<<"test 54\n";
          if (err == 1) {
              cerr<<"erreur lors de la création du coup";
              return -1;
          }
          packet.is(coup);
            std::cout<<"test 55\n";
          if(gf::SocketStatus::Data != socket.sendPacket(packet))
          {
              cerr<<"erreur lors de l'envoi de coup";
              return -1;
          }
            std::cout<<"test 56\n";
          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              return -1;
          }
            //cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            std::cout<<"test 57\n";
            //plateau.printMovePiece();
            std::cout<<"test 58\n";
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
            
            std::cout<<"test 59\n";
        }
        cout<<plateau.afficheTerminal();
        
    }

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
    return 0;
}
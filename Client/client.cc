#include <iostream>
#include<cstring>
#include<string>

#include <string>
#include <vector>

#include <gf/TcpSocket.h>
#include <gf/Packet.h>
#include <gf/Id.h>
#include <gf/SerializationOps.h>

#include "../protocole/protocole.h"
#include "../model/Plateau.h"
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
    req.nomJoueur = "joueur 1"; // à modifier
    req.coulPion = 1;

    gf::Packet packet;
    packet.is(req);
    if(gf::SocketStatus::Data != socket.sendPacket(packet))
    {
        cerr<<"erreur lors de l'envoi de demande partie au serveur";
        socket.~TcpSocket();
        return -1;
    }


    if( gf::SocketStatus::Data != socket.recvPacket(packet))
    {
        cerr<<"erreur lors de la réception de confirmation de partie du serveur";
        socket.~TcpSocket();
        return -1;
    }

    auto repPartie = packet.as<PartieRep>();


    int couleur = initColor(repPartie.validCoulPion, req.coulPion);

    cout<<"Vous jouez la couleur : "<<couleur<<" \n";

    /************** Début de partie ********************/
    Plateau plateau = Plateau();
    
    while (true)
    {
        cout<<"Etat du plateau :\n"<<plateau.afficheTerminal(); 

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
              socket.~TcpSocket();
              return -1;
          }
          std::cout<<"testC0\n";
          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }
          std::cout<<"testC1\n";
          cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();

            auto coupRep = packet.as<TCoupRep>();


          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdv = packet.as<TCoupReq>();

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdvRep = packet.as<TCoupRep>();

          if(coupAdvRep.propCoup == CONT)
          {
            if(coupAdvRep.validCoup == VALID)
            {
                modifCoupAdv(coupAdv, plateau, 1);
                cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            }
          }
          else
          {
            /* la partie est fini, il faut afficher le résultat */
            break;
          }

        }
        else
        {

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdv = packet.as<TCoupReq>();

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdvRep = packet.as<TCoupRep>();

          if(coupAdvRep.propCoup == CONT)
          {
            if(coupAdvRep.validCoup == VALID)
            {
                modifCoupAdv(coupAdv, plateau, -1);
                cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();
            }
          }
          else
          {
            /* la partie est fini, il faut afficher le résultat */
            break;
          }

          TCoupReq coup = buildCoup(plateau, -1, err);

          if (err == 1) {
              cerr<<"erreur lors de la création du coup";
              return -1;
          }
          packet.is(coup);
          if(gf::SocketStatus::Data != socket.sendPacket(packet))
          {
              cerr<<"erreur lors de l'envoi de coup";
              socket.~TcpSocket();
              return -1;
          }

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }
            cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();

            auto coupRep = packet.as<TCoupRep>();
          
        }
        
    }

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
     socket.~TcpSocket();
    return 0;
}
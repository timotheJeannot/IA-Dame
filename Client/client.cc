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
using namespace gf::literals;
using namespace std;

struct integer {
    static constexpr gf::Id type = "integer"_id;
    int nb;
};

template<typename Archive>
  Archive operator|(Archive& ar, integer& data) {
    return ar |data.nb ;
  }

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
    // pour l'instant on va mettre blanc 

    /*TPartieReq req;
    req.idReq = PARTIE;
    strcpy(req.nomJoueur,argv[3]);
    req.coulPion = BLANC;

    gf::Packet packetTest;*/

    //packetTest.is(req);
    /*struct integer data;
    data.nb = 0;
    cout<<"rentrez un int \n";
    cin>>data.nb;
    gf::Packet packet;
    packet.is(data);
    socket.sendPacket(packet);*/

    PartieReq req;
    req.idReq = PARTIE;
    req.nomJoueur = "joueur 1"; // à modifier
    req.coulPion = BLANC;

    gf::Packet packet;
    packet.is(req);
    if(gf::SocketStatus::Data != socket.sendPacket(packet))
    {
        cerr<<"erreur lors de l'envoie de demande partie au serveur";
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

    Coul couleur ;
    if(repPartie.validCoulPion == OK)
    {
      couleur = (req.coulPion == BLANC)? BLANC : NOIR;
    }
    else
    {
      couleur = (req.coulPion == BLANC)? NOIR : BLANC;
    }
    
    

    /************** Début de partie ********************/
    while (true)
    {
        if(couleur == BLANC) // On commence
        {
          
          CoupReq coup ;
          coup.idRequest = COUP;
          coup.estBloque = false;
          Pion pion ;
          pion.coulPion = couleur;
          pion.typePion = PION;
          coup.pion = pion;
          coup.propCoup = CONT ;

          cout<<"Donnez la coordonnée vertical pour le choix de la pièce \n";
          int x;
          cin>>x;
          cout<<"Donnez la coordonnée horizontal pour le choix de la pièce \n";
          int y ;
          cin>>y;

          Case c;
          c.l = Num (y);
          c.c = (Num) x;

          coup.posPionAv = c;

          cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
          cin>>x;
          cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
          cin>>y;

          c.l = Num (y);
          c.c = (Num) x;

          coup.posPionAp = c;

          packet.is(coup);
          if(gf::SocketStatus::Data != socket.sendPacket(packet))
          {
              cerr<<"erreur lors de l'envoie de coup";
              socket.~TcpSocket();
              return -1;
          }

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupRep = packet.as<CoupRep>();


          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdv = packet.as<CoupReq>();

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdvRep = packet.as<CoupRep>();
          


        }
        else
        {

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdv = packet.as<CoupReq>();

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupAdvRep = packet.as<CoupRep>();

          CoupReq coup ;
          coup.idRequest = COUP;
          coup.estBloque = false;
          Pion pion ;
          pion.coulPion = couleur;
          pion.typePion = PION;
          coup.pion = pion;
          coup.propCoup = CONT ;

          cout<<"Donnez la coordonnée vertical pour le choix de la pièce \n";
          int x;
          cin>>x;
          cout<<"Donnez la coordonnée horizontal pour le choix de la pièce \n";
          int y ;
          cin>>y;

          Case c;
          c.l = Num (y);
          c.c = (Num) x;

          coup.posPionAv = c;

          cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
          cin>>x;
          cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
          cin>>y;

          c.l = Num (y);
          c.c = (Num) x;

          coup.posPionAp = c;

          packet.is(coup);
          if(gf::SocketStatus::Data != socket.sendPacket(packet))
          {
              cerr<<"erreur lors de l'envoie de coup";
              socket.~TcpSocket();
              return -1;
          }

          if( gf::SocketStatus::Data != socket.recvPacket(packet))
          {
              cerr<<"erreur lors de la réception de confirmation de partie du serveur";
              socket.~TcpSocket();
              return -1;
          }

          auto coupRep = packet.as<CoupRep>();

          

          
        }
        
    }
    

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
     socket.~TcpSocket();
    return 0;
}
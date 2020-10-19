#include <iostream>
#include<cstring>
#include<string>

#include <gf/TcpSocket.h>
#include <gf/Packet.h>

#include "protocole.h"

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
    // pour l'instant on va mettre blanc 

    TPartieReq req;
    req.idReq = PARTIE;
    strcpy(req.nomJoueur,argv[3]);
    req.coulPion = BLANC;

    gf::Packet packetTest;
    //packetTest.is(req);

    

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
     socket.~TcpSocket();
    return 0;
}
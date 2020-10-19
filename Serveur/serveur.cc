#include <iostream>
#include<string>

#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>

#include "../protocole/protocole.h"

using namespace std;

int main(int argc, char ** argv)
{
    /* verification des arguments */
    if (argc != 2) {
        //printf("usage : %s nom/IPServ port nomJoueur \n", argv[0]);
        cout<<"usage "<<argv[0]<<" port\n";
        return -1;
    }
    cout<<"test1\n";
    /************ Initialisation de la communication **********/
    int port = atoi(argv[1]);
    cout<<"test2\n";
    //attente de la communication avec le client
    gf::TcpListener listener(to_string(port));

    for (;;) {
        // Accept a new connection ...
        gf::TcpSocket client = listener.accept();
        if (client) {
        // and handle the client...
            cout<<"debut de communication avec un client \n";
            
        }

        //fin de la connection
        client.~TcpSocket();
    }
    

    
    return 0;
}
#include <iostream>
#include<string>

#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Packet.h>

#include "../protocole/protocole.h"
using namespace gf::literals;
using namespace std;

struct integer {
    static constexpr gf::Id type = "integer"_id;
    int nb;
};


template<typename Archive>
  Archive operator|(Archive& ar, integer& data) {
    return ar | data.nb ;
  }


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
            
            gf::TcpSocket client2 = listener.accept();
            if (client2) {
                cout<<"debut de communication avec le second client \n";
                gf::Packet packetC1;
                gf::Packet packetC2;

                if( gf::SocketStatus::Error == client.recvPacket(packetC1))
                {
                  cerr<<"erreur lors de la réception du packet du client 1";
                }
                else
                {
                    /*
                    auto data1 = packetC1.as<integer>();
                    cout <<"le serveur a recu de la part de c1 : "<<data1.nb<<"\n";
                    */

                   auto req = packetC1.as<PartieReq>();
                   cout<<req.nomJoueur<<"\n";
                }
                
                if( gf::SocketStatus::Error == client2.recvPacket(packetC2))
                {
                    cerr<<"erreur lors de la réception du packet du client 2";
                }
                else
                {
                   auto req = packetC2.as<PartieReq>();
                    //cout <<"le serveur a recu de la part de c2 : "<<data2.nb<<"\n";
                    cout<<req.nomJoueur<<"\n";
                }
                

            }
        }

        

        //fin de la connection
        client.~TcpSocket();
    }
    

    
    return 0;
}
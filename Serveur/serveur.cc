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

    
    // Accept a new connection ...
    gf::TcpSocket client1 = listener.accept();
    if (client1) {
    // and handle the client...
        cout<<"debut de communication avec un client \n";
        
        gf::TcpSocket client2 = listener.accept();
        if (client2) {
            cout<<"debut de communication avec le second client \n";
            gf::Packet packetC1;
            gf::Packet packetC2;

            if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
            {
                cerr<<"erreur lors de la réception du packet du client 1";
                client1.~TcpSocket();
                client2.~TcpSocket();
                return -1;
            }
            
            auto req1 = packetC1.as<TPartieReq>();
            cout<<req1.nomJoueur<<"\n";
            
            
            if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
                client1.~TcpSocket();
                client2.~TcpSocket();
                return -1;
            }

            
            auto req2 = packetC2.as<TPartieReq>();
            cout<<req2.nomJoueur<<"\n";

            /*******         Envoie de la validation de la requête de partie            ********/

            PartieRep rep1 ;
            rep1.err = ERR_OK;
            rep1.nomAdvers = req2.nomJoueur;
            rep1.validCoulPion = OK;

            packetC1.is(rep1);
            if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
                client1.~TcpSocket();
                client2.~TcpSocket();
            }

            PartieRep rep2;
            rep2.err = ERR_OK;
            rep2.nomAdvers = req1.nomJoueur;
            if(req1.coulPion == req2.coulPion)
            {                   
                rep2.validCoulPion = KO;             
            }
            else
            {
                rep2.validCoulPion = OK;
            }

            packetC2.is(rep2);
            if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
                client1.~TcpSocket();
                client2.~TcpSocket();
            }
            
            /****** Boucle de jeu ********/
            while(true)
            {
                // le joueur 1 est blanc
                if(req1.coulPion == BLANC)
                {
                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 1";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coup = packetC1.as<TCoupReq>();

                    cout<<"la position x du pion avant "<<(int) coup.posPionAv.c<<"\n";

                    TCoupRep coupRep ;
                    coupRep.err =ERR_OK;
                    coupRep.validCoup = VALID;
                    coupRep.propCoup = CONT;

                    
                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC2.is(coup);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coupC2 = packetC2.as<TCoupReq>();

                    cout<<"(adv) la position x du pion avant "<<(int) coupC2.posPionAv.c<<"\n";

                    coupRep.err =ERR_OK;
                    coupRep.validCoup = VALID;
                    coupRep.propCoup = CONT;

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC1.is(coupC2);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    

                }
                else // le joueur 2 est blanc
                {
                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coup = packetC2.as<TCoupReq>();

                    cout<<"la position x du pion avant "<<(int) coup.posPionAv.c<<"\n";

                    TCoupRep coupRep ;
                    coupRep.err =ERR_OK;
                    coupRep.validCoup = VALID;
                    coupRep.propCoup = CONT;

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC1.is(coup);
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC1.is(coupRep);
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 1";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coupC1 = packetC1.as<TCoupReq>();

                    cout<<"(adv) la position x du pion avant "<<(int) coupC1.posPionAv.c<<"\n";

                    coupRep.err =ERR_OK;
                    coupRep.validCoup = VALID;
                    coupRep.propCoup = CONT;

                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC2.is(coupC1);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                    }


                }
            }
            
            

            

        }

        client2.~TcpSocket();
    }

    

    //fin de la connection
    client1.~TcpSocket();
        
    
    

    
    return 0;
}
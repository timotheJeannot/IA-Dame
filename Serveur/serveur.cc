#include <iostream>
#include<string>

#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Packet.h>

#include "../protocole/protocole.h"
#include "../model/Plateau.h"
#include "serverTools.h"
using namespace gf::literals;
using namespace std;


int main(int argc, char ** argv)
{

    /* verification des arguments */
    if (argc != 2) {
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
                return -1;
            }
            
            auto req1 = packetC1.as<TPartieReq>();
            cout<<req1.nomJoueur<<"\n";
            
            
            if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
                return -1;
            }

            
            auto req2 = packetC2.as<TPartieReq>();
            cout<<req2.nomJoueur<<"\n";

            /*******         Envoie de la validation de la requête de partie            ********/


            std::vector<PartieRep> partieRep;
            partieRep = buildRepPartie(req1, req2);

            packetC1.is(partieRep.at(0));
            if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
            }

            packetC2.is(partieRep.at(1));
            if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
            }
            
            Plateau plateau = Plateau();
            // on va compter les pièces restantes pour savoir quand la partie est terminé
            int nbPieceNoir = 15;
            int nbPieceBlanche = 15;
            /****** Boucle de jeu ********/
            while(true)
            {
                // le joueur 1 est blanc
                if(req1.coulPion == 1)
                {
                    std::cout<<"test 0 debut serv \n";
                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 1";
                        return -1;
                    }
                    std::cout<<"test 1";

                    auto coup = packetC1.as<TCoupReq>();

                    TCoupRep coupRep = buildRepCoup(plateau, coup, nbPieceNoir, 0);

                    cout<<plateau.afficheTerminal();

                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";

                    }

                    packetC2.is(coup);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";

                    }

                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        break;                       
                    }

                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        return -1;
                    }

                    auto coupC2 = packetC2.as<TCoupReq>();

                    coupRep = buildRepCoup(plateau, coupC2, nbPieceBlanche, 1);
                    cout<<plateau.afficheTerminal();

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }

                    packetC1.is(coupC2);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }

                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }

                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        break;                       
                    }

                }
                else // le joueur 2 est blanc
                {
                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        return -1;
                    }

                    auto coupC2 = packetC2.as<TCoupReq>();

                    TCoupRep coupRep = buildRepCoup(plateau, coupC2, nbPieceBlanche, 1);
                    cout<<plateau.afficheTerminal();

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";

                    }

                    packetC1.is(coupC2);
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";

                    }

                    packetC1.is(coupRep);
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";

                    }
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        break;                       
                    }

                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 1";

                        return -1;
                    }

                    auto coupC1 = packetC1.as<TCoupReq>();


                    coupRep = buildRepCoup(plateau, coupC1, nbPieceNoir, 0);
                    cout<<plateau.afficheTerminal();

                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }

                    packetC2.is(coupC1);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }

                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                    }
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        break;                       
                    }

                }
            }
   

        }

        client2.~TcpSocket();
    }

    client1.~TcpSocket();
          
    return 0;
}
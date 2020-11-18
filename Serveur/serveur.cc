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
    //cout<<"test1\n";
    /************ Initialisation de la communication **********/
    int port = atoi(argv[1]);
    //cout<<"test2\n";
    //attente de la communication avec le client
    gf::TcpListener listener(to_string(port));

    
    // Accept a new connection ...
    gf::TcpSocket client1 = listener.accept();
    if (client1) {
    // and handle the client...
        //cout<<"debut de communication avec un client \n";
        
        gf::TcpSocket client2 = listener.accept();
        if (client2) {
            //cout<<"debut de communication avec le second client \n";
            gf::Packet packetC1;
            gf::Packet packetC2;

            if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
            {
                cerr<<"erreur lors de la réception du packet du client 1";
                return -1;
            }
            
            auto req1 = packetC1.as<TPartieReq>();
            //cout<<req1.nomJoueur<<"\n";
            
            
            if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
            {
                cerr<<"erreur lors de la réception du packet du client 2";
                return -1;
            }

            
            auto req2 = packetC2.as<TPartieReq>();
            //cout<<req2.nomJoueur<<"\n";

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
            
            //Plateau plateau = Plateau();
            //Plateau plateau();
            Plateau plateau;
            
            std::vector<Plateau> configs ; // d'après wikipédia , pour la partie nulle : quand la même position des pièces se produit pour la troisième fois, et que c'est au même joueur de jouer 
                                           // on va stocker les états du plateau successif lors d'un déplacement d'une dame sans prise
                                           // pour les autres déplacements on va clear cette liste (impossible de se retrouver dans la config d'avant le déplacement).
            
            int first =0;                  // cet entier vaudra 1 ou -1 pour indiquer qui est le premier à avoir bouger une dame, pour qu'on puisse s'y retroiver dans la liste du dessus
            
            int compteurR2 = 0;            // compteur pour la deuxième règle de nulle (décrit dans serverTools.h)
            int compteurR3 = 0;            // compteur pour la troisième règle de nulle (décrit dans serverTools.h)
            int firstR3 = 0 ;              // permet de savoir quel était le premier joueur (blanc ou noir) lors du début du comptage des 16 coups pour chaque joueur

            //cout<<plateau.afficheTerminal();
            /****** Boucle de jeu ********/
            while(true)
            {
                if(firstR3 == 1)
                {
                    compteurR3 ++;
                }

                //cout<<"Attention : nbPieceB = "<<to_string(plateau.getNbPiecesB())<<"  nbPieceN = "<<to_string(plateau.getNbPiecesN())<<"\n";
                // le joueur 1 est blanc
                if(req1.coulPion == 1)
                {
                    //cout<<"test 0 debut serv \n";
                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet qui contient le coup du client 1";
                        return -1;
                    }
                    //cout<<"test 1";

                    auto coup = packetC1.as<TCoupReq>();
                    //cout<<"test 60\n";

                    if(firstR3 == 0)
                    {
                        if(r3DetectConfig(plateau))
                        {
                            firstR3 = 1;
                        }
                    }

                    TCoupRep coupRep = buildRepCoup(plateau, coup, 1,configs,first,compteurR2,compteurR3);
                    if(firstR3 == -1)
                    {
                        compteurR3 ++;
                    }
                    //cout<<"test 61\n";
                    //cout<<plateau.afficheTerminal();

                    packetC1.is(coupRep);
                    //cout<<"test 62\n";
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de l'envoie du packet coupRep (du coup du client 1) au client 1";

                    }
                    //cout<<"test 63\n";
                    packetC2.is(coup);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de l'envoie du packet coup (du coup du client 1) au client 2";
                    }
                    //cout<<"test 64\n";
                    packetC2.is(coupRep);

                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de l'envoie du packet coupRep (du coup du client 1) au client 2";

                    }
                    //cout<<"test 65\n";
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 1("<<req1.nomJoueur<<") a gagné \n";
                        break;                       
                    }
                    if(coupRep.propCoup == NUL)
                    {
                        cout<<"match nul \n";
                        break;
                    }
                    if(coupRep.propCoup ==PERDU)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 1("<<req1.nomJoueur<<") a gagné \n";
                        break;                       
                    }

                    //cout<<"test 66\n";
                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet qui contient le coup du client 2";
                        return -1;
                    }
                    //cout<<"test 67\n";
                    auto coupC2 = packetC2.as<TCoupReq>();
                    //cout<<"test 68\n";
                    if(firstR3 == 0)
                    {
                        if(r3DetectConfig(plateau))
                        {
                            firstR3 = -1;
                        }
                    }
                    coupRep = buildRepCoup(plateau, coupC2, -1,configs,first,compteurR2,compteurR3);
                    //cout<<plateau.afficheTerminal();

                    packetC2.is(coupRep);
                    //cout<<"test 69\n";
                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"erreur lors de l'envoie du packet coupRep (du coup du client 2) au client 2";
                    }
                    //cout<<"test 70\n";
                    packetC1.is(coupC2);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de l'envoie du packet coup (du coup du client 2) au client 1";
                    }
                    //cout<<"test 71\n";
                    packetC1.is(coupRep);

                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"erreur lors de l'envoie du packet coupRep (du coup du client 2) au client 1";
                    }
                    //cout<<"test 72\n";
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 2("<<req2.nomJoueur<<") a gagné \n";
                        break;                       
                    }
                    if(coupRep.propCoup == NUL)
                    {
                        cout<<"match nul \n";
                        break;
                    }
                    if(coupRep.propCoup ==PERDU)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 1("<<req1.nomJoueur<<") a gagné \n";
                        break;                       
                    }

                }
                else // le joueur 2 est blanc
                {
                    //cout<<"test 73\n";
                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"(2)erreur lors de la réception du packet qui contient le coup du client 2";
                        return -1;
                    }

                    auto coupC2 = packetC2.as<TCoupReq>();
                    //cout<<"test 74\n";
                    if(firstR3 == 0)
                    {
                        if(r3DetectConfig(plateau))
                        {
                            firstR3 = 1;
                        }
                    }
                    TCoupRep coupRep = buildRepCoup(plateau, coupC2, 1,configs,first, compteurR2,compteurR3);
                    if(firstR3 == -1)
                    {
                        compteurR3 ++;
                    }
                    //cout<<plateau.afficheTerminal();

                    packetC2.is(coupRep);
                    //cout<<"test 75\n";
                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"(2)erreur lors de l'envoie du packet coupRep (du coup du client 2) au client 2";

                    }
                    //cout<<"test 76\n";
                    packetC1.is(coupC2);
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"(2)erreur lors de l'envoie du packet coup (du coup du client 2) au client 1";

                    }
                    //cout<<"test 77\n";
                    packetC1.is(coupRep);
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"(2)erreur lors de l'envoie du packet coupRep (du coup du client 2) au client 1";

                    }
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 2("<<req2.nomJoueur<<") a gagné \n";
                        break;                       
                    }
                    if(coupRep.propCoup == NUL)
                    {
                        cout<<"match nul \n";
                        break;
                    }
                    if(coupRep.propCoup ==PERDU)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 1("<<req1.nomJoueur<<") a gagné \n";
                        break;                       
                    }
                    //cout<<"test 78\n";
                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"(2)erreur lors de la réception du packet qui contient le coup du client 1";

                        return -1;
                    }
                    //cout<<"test 79\n";
                    auto coupC1 = packetC1.as<TCoupReq>();
                    //cout<<"test 80\n";

                    if(firstR3 == 0)
                    {
                        if(r3DetectConfig(plateau))
                        {
                            firstR3 = -1;
                        }
                    }

                    coupRep = buildRepCoup(plateau, coupC1, -1,configs,first, compteurR2,compteurR3);
                    //cout<<plateau.afficheTerminal();

                    packetC1.is(coupRep);
                    //cout<<"test 81\n";
                    if(gf::SocketStatus::Data != client1.sendPacket(packetC1))
                    {
                        cerr<<"(2)erreur lors de l'envoie du packet coupRep (du coup du client 1) au client 1";
                    }

                    packetC2.is(coupC1);
                    //cout<<"test 82\n";
                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"(2)erreur lors de l'envoie du packet coup (du coup du client 1) au client 2";
                    }

                    packetC2.is(coupRep);
                    //cout<<"test 83\n";
                    if(gf::SocketStatus::Data != client2.sendPacket(packetC2))
                    {
                        cerr<<"(2)erreur lors de l'envoie du packet coupRep (du coup du client 1) au client 2";
                    }
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 1("<<req1.nomJoueur<<") a gagné \n";
                        break;                       
                    }
                    if(coupRep.propCoup == NUL)
                    {
                        cout<<"match nul \n";
                    }
                    if(coupRep.propCoup ==PERDU)// fin du jeu et de la communication
                    {
                        cout<<"le joueur 2("<<req1.nomJoueur<<") a gagné \n";
                        break;                       
                    }
                    //cout<<"test 84\n";
                }
            }
   

        }

        client2.~TcpSocket();
    }

    client1.~TcpSocket();
          
    return 0;
}
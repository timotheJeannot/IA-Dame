#include <iostream>
#include<string>

#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Packet.h>

#include "../protocole/protocole.h"
#include "../model/Plateau.h"
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
            
            Plateau plateau = Plateau();
            // on va compter les pièces restantes pour savoir quand la partie est terminé
            int nbPieceNoir = 15;
            int nbPieceBlanche = 15;
            /****** Boucle de jeu ********/
            while(true)
            {
                // le joueur 1 est blanc
                if(req1.coulPion == BLANC)
                {
                    std::cout<<"test 0 debut serv \n";
                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 1";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }
                    std::cout<<"test 1";

                    auto coup = packetC1.as<TCoupReq>();

                    std::vector<TCase> deplacementsJ1 = coup.deplacements;
                    TCase posPionAvJ1= coup.posPionAv;
                    int xJ1 = (int) posPionAvJ1.c;
                    int yJ1 = (int) posPionAvJ1.l;
                    Pion pJ1;
                    Dame dJ1 ;
                    bool isDameJ1 = false;
                    bool usePieceAdv = false;
                    bool testErrCoup = false;
                    if(plateau.getPlateau()[xJ1][yJ1] <0)
                    {
                        usePieceAdv = true;
                    }
                    else
                    {
                        if(plateau.getPlateau()[xJ1][yJ1] == 1)
                        {
                            pJ1 = Pion(xJ1,yJ1,true);
                        }
                        else
                        {
                            dJ1 = Dame(xJ1,yJ1,true);
                            isDameJ1 = true;
                        }

                        int size = deplacementsJ1.size();                       
                        if(isDameJ1)
                        {
                            TCase cnextJ1 = deplacementsJ1[0];
                            int x2J1 = (int) cnextJ1.c;
                            int y2J1 = (int) cnextJ1.l;
                            Case cibleJ1(x2J1,y2J1);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(dJ1,cibleJ1);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size != 1))
                            {
                                testErrCoup = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceNoir --;
                            
                                for(int i = 1 ; i <size; i++)
                                {
                                    cnextJ1 = deplacementsJ1[i];
                                    x2J1 = (int) cnextJ1.c;
                                    y2J1 = (int) cnextJ1.l;
                                    cibleJ1.setColonne(x2J1);
                                    cibleJ1.setLigne(y2J1);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(dJ1,cibleJ1); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size-1))
                                    {
                                        testErrCoup = true;
                                    }

                                }
                            }
                            nbPieceNoir = nbPieceNoir - size +1;
                        }
                        else
                        {
                            TCase cnextJ1 = deplacementsJ1[0];
                            int x2J1 = (int) cnextJ1.c;
                            int y2J1 = (int) cnextJ1.l;
                            Case cibleJ1(x2J1,y2J1);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(pJ1,cibleJ1);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size != 1))
                            {
                                testErrCoup = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceNoir --;
                            
                                for(int i = 1 ; i <size; i++)
                                {
                                    cnextJ1 = deplacementsJ1[i];
                                    x2J1 = (int) cnextJ1.c;
                                    y2J1 = (int) cnextJ1.l;
                                    cibleJ1.setColonne(x2J1);
                                    cibleJ1.setLigne(y2J1);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(pJ1,cibleJ1); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size-1))
                                    {
                                        testErrCoup = true;
                                    }

                                }
                            }
                            nbPieceNoir = nbPieceNoir - size +1;
                        }
                        plateau.enleverPiecesRafle();                   
                    }
                    TCoupRep coupRep ;
                    if(testErrCoup || usePieceAdv)
                    {
                        coupRep.err = ERR_COUP;
                        coupRep.validCoup = TRICHE ; // je fais pas bien la différence entre ces deux infos du protocole
                        //coupRep.propCoup = PERDU; // faut t'il envoyer ça à ce moment ?
                    }
                    else
                    {
                        coupRep.err =ERR_OK;
                        coupRep.validCoup = VALID;
                        cout<<plateau.afficheTerminal();
                    }
                    if(nbPieceNoir == 0)
                    {
                        coupRep.propCoup = GAGNE;
                    }
                    else
                    {
                        coupRep.propCoup = CONT;
                    }

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

                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        break;                       
                    }

                    if( gf::SocketStatus::Data != client2.recvPacket(packetC2))
                    {
                        cerr<<"erreur lors de la réception du packet du client 2";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coupC2 = packetC2.as<TCoupReq>();

                    std::vector<TCase> deplacementsJ2= coupC2.deplacements;
                    TCase posPionAvJ2= coupC2.posPionAv;
                    int xJ2 = (int) posPionAvJ2.c;
                    int yJ2 = (int) posPionAvJ2.l;
                    Pion pJ2;
                    Dame dJ2 ;
                    bool isDameJ2 = false;
                    usePieceAdv = false;
                    bool testErrCoup2 = false;
                    if(plateau.getPlateau()[xJ2][yJ2] >0)
                    {
                        usePieceAdv = true;
                    }
                    else
                    {                    
                        if(plateau.getPlateau()[xJ2][yJ2] == -1)
                        {
                            pJ2 = Pion(xJ2,yJ2,false);
                        }
                        else
                        {
                            dJ2 = Dame(xJ2,yJ2,false);
                            isDameJ2 = true;
                        }

                        int size2 = deplacementsJ2.size();                        
                        if(isDameJ2)
                        {
                            TCase cnextJ2 = deplacementsJ2[0];
                            int x2J2 = (int) cnextJ2.c;
                            int y2J2 = (int) cnextJ2.l;
                            Case cibleJ2(x2J2,y2J2);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(dJ2,cibleJ2);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size2 != 1))
                            {
                                testErrCoup2 = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceBlanche --;
                            
                                for(int i = 1 ; i <size2; i++)
                                {
                                    cnextJ2 = deplacementsJ2[i];
                                    x2J2 = (int) cnextJ2.c;
                                    y2J2 = (int) cnextJ2.l;
                                    cibleJ2.setColonne(x2J2);
                                    cibleJ2.setLigne(y2J2);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(dJ2,cibleJ2); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                                    {
                                        testErrCoup2 = true;
                                    }

                                }
                            }
                            nbPieceBlanche = nbPieceBlanche - size2 +1;
                        }
                        else
                        {
                            TCase cnextJ2 = deplacementsJ2[0];
                            int x2J2 = (int) cnextJ2.c;
                            int y2J2 = (int) cnextJ2.l;
                            Case cibleJ2(x2J2,y2J2);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(pJ2,cibleJ2);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size2 != 1))
                            {
                                testErrCoup2 = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceBlanche --;
                            
                                for(int i = 1 ; i <size2; i++)
                                {
                                    cnextJ2 = deplacementsJ2[i];
                                    x2J2 = (int) cnextJ2.c;
                                    y2J2 = (int) cnextJ2.l;
                                    cibleJ2.setColonne(x2J2);
                                    cibleJ2.setLigne(y2J2);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(pJ2,cibleJ2); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                                    {
                                        testErrCoup2 = true;
                                    }
                                }
                            }
                            nbPieceBlanche = nbPieceBlanche - size2 +1;
                        }
                        plateau.enleverPiecesRafle(); 
                    }

                    if(testErrCoup2 || usePieceAdv)
                    {
                        coupRep.err = ERR_COUP;
                        coupRep.validCoup = TRICHE ; // je fais pas bien la différence entre ces deux infos du protocole
                        //coupRep.propCoup = PERDU; // faut t'il envoyer ça à ce moment ?
                    }
                    else
                    {
                        coupRep.err =ERR_OK;
                        coupRep.validCoup = VALID;
                        cout<<plateau.afficheTerminal();
                    }
                    if(nbPieceBlanche == 0)
                    {
                        coupRep.propCoup = GAGNE;
                    }
                    else
                    {
                        coupRep.propCoup = CONT;
                    }

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
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coupC2 = packetC2.as<TCoupReq>();

                    std::vector<TCase> deplacementsJ2= coupC2.deplacements;
                    TCase posPionAvJ2= coupC2.posPionAv;
                    int xJ2 = (int) posPionAvJ2.c;
                    int yJ2 = (int) posPionAvJ2.l;
                    Pion pJ2;
                    Dame dJ2 ;
                    bool isDameJ2 = false;
                    bool usePieceAdv = false;
                    bool testErrCoup2 = false;
                    if(plateau.getPlateau()[xJ2][yJ2] <0)
                    {
                        usePieceAdv = true;
                    }
                    else
                    {
                        if(plateau.getPlateau()[xJ2][yJ2] == 1)
                        {
                            pJ2 = Pion(xJ2,yJ2,true);
                        }
                        else
                        {
                            dJ2 = Dame(xJ2,yJ2,true);
                            isDameJ2 = true;
                        }

                        int size2 = deplacementsJ2.size();
                        if(isDameJ2)
                        {
                            TCase cnextJ2 = deplacementsJ2[0];
                            int x2J2 = (int) cnextJ2.c;
                            int y2J2 = (int) cnextJ2.l;
                            Case cibleJ2(x2J2,y2J2);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(dJ2,cibleJ2);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size2 != 1))
                            {
                                testErrCoup2 = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceNoir --;
                            
                                for(int i = 1 ; i <size2; i++)
                                {
                                    cnextJ2 = deplacementsJ2[i];
                                    x2J2 = (int) cnextJ2.c;
                                    y2J2 = (int) cnextJ2.l;
                                    cibleJ2.setColonne(x2J2);
                                    cibleJ2.setLigne(y2J2);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(dJ2,cibleJ2); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                                    {
                                        testErrCoup2 = true;
                                    }

                                }
                            }
                            nbPieceNoir = nbPieceNoir - size2 +1;
                        }
                        else
                        {
                            TCase cnextJ2 = deplacementsJ2[0];
                            int x2J2 = (int) cnextJ2.c;
                            int y2J2 = (int) cnextJ2.l;
                            Case cibleJ2(x2J2,y2J2);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(pJ2,cibleJ2);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size2 != 1))
                            {
                                testErrCoup2 = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceNoir --;
                            
                                for(int i = 1 ; i <size2; i++)
                                {
                                    cnextJ2 = deplacementsJ2[i];
                                    x2J2 = (int) cnextJ2.c;
                                    y2J2 = (int) cnextJ2.l;
                                    cibleJ2.setColonne(x2J2);
                                    cibleJ2.setLigne(y2J2);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(pJ2,cibleJ2); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size2-1))
                                    {
                                        testErrCoup2 = true;
                                    }
                                }
                            }
                            nbPieceNoir = nbPieceNoir - size2 +1;
                        }
                        plateau.enleverPiecesRafle(); 

                    }
                    TCoupRep coupRep ;

                    if(testErrCoup2 || usePieceAdv)
                    {
                        coupRep.err = ERR_COUP;
                        coupRep.validCoup = TRICHE ; // je fais pas bien la différence entre ces deux infos du protocole
                        //coupRep.propCoup = PERDU; // faut t'il envoyer ça à ce moment ?
                    }
                    else
                    {
                        coupRep.err =ERR_OK;
                        coupRep.validCoup = VALID;
                        cout<<plateau.afficheTerminal();
                    }
                    if(nbPieceNoir == 0)
                    {
                        coupRep.propCoup = GAGNE;
                    }
                    else
                    {
                        coupRep.propCoup = CONT;
                    }

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
                    if(coupRep.propCoup ==GAGNE)// fin du jeu et de la communication
                    {
                        break;                       
                    }

                    if( gf::SocketStatus::Data != client1.recvPacket(packetC1))
                    {
                        cerr<<"erreur lors de la réception du packet du client 1";
                        client1.~TcpSocket();
                        client2.~TcpSocket();
                        return -1;
                    }

                    auto coupC1 = packetC1.as<TCoupReq>();

                    std::vector<TCase> deplacementsJ1 = coupC1.deplacements;
                    TCase posPionAvJ1= coupC1.posPionAv;
                    int xJ1 = (int) posPionAvJ1.c;
                    int yJ1 = (int) posPionAvJ1.l;
                    Pion pJ1;
                    Dame dJ1 ;
                    bool isDameJ1 = false;
                    usePieceAdv = false;
                    bool testErrCoup = false;
                    if(plateau.getPlateau()[xJ1][yJ1] >0)
                    {
                        usePieceAdv = true;
                    }
                    else
                    {
                        if(plateau.getPlateau()[xJ1][yJ1] == -1)
                        {
                            pJ1 = Pion(xJ1,yJ1,false);
                        }
                        else
                        {
                            dJ1 = Dame(xJ1,yJ1,false);
                            isDameJ1 = true;
                        }

                        int size = deplacementsJ1.size();
                        
                        if(isDameJ1)
                        {
                            TCase cnextJ1 = deplacementsJ1[0];
                            int x2J1 = (int) cnextJ1.c;
                            int y2J1 = (int) cnextJ1.l;
                            Case cibleJ1(x2J1,y2J1);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(dJ1,cibleJ1);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size != 1))
                            {
                                testErrCoup = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceBlanche --;
                            
                                for(int i = 1 ; i <size; i++)
                                {
                                    cnextJ1 = deplacementsJ1[i];
                                    x2J1 = (int) cnextJ1.c;
                                    y2J1 = (int) cnextJ1.l;
                                    cibleJ1.setColonne(x2J1);
                                    cibleJ1.setLigne(y2J1);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(dJ1,cibleJ1); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size-1))
                                    {
                                        testErrCoup = true;
                                    }

                                }
                            }
                            nbPieceBlanche = nbPieceBlanche - size +1;
                        }
                        else
                        {
                            TCase cnextJ1 = deplacementsJ1[0];
                            int x2J1 = (int) cnextJ1.c;
                            int y2J1 = (int) cnextJ1.l;
                            Case cibleJ1(x2J1,y2J1);
                            int retModifDeplacement = plateau.modifPlateauDeplacementNormal(pJ1,cibleJ1);
                            if(retModifDeplacement == -1 || (retModifDeplacement == 0 && size != 1))
                            {
                                testErrCoup = true;
                            }
                            if(retModifDeplacement == 1)
                            {
                                nbPieceBlanche --;
                            
                                for(int i = 1 ; i <size; i++)
                                {
                                    cnextJ1 = deplacementsJ1[i];
                                    x2J1 = (int) cnextJ1.c;
                                    y2J1 = (int) cnextJ1.l;
                                    cibleJ1.setColonne(x2J1);
                                    cibleJ1.setLigne(y2J1);
                                    retModifDeplacement = plateau.modifPlateauDeplacementPrise(pJ1,cibleJ1); 
                                    if(retModifDeplacement == -1 || (retModifDeplacement == 0 && i < size-1))
                                    {
                                        testErrCoup = true;
                                    }

                                }
                            }
                            nbPieceBlanche = nbPieceBlanche - size +1;
                        }
                        plateau.enleverPiecesRafle();
                    }
                    if(testErrCoup||usePieceAdv)
                    {
                        coupRep.err = ERR_COUP;
                        coupRep.validCoup = TRICHE ; // je fais pas bien la différence entre ces deux infos du protocole
                        //coupRep.propCoup = PERDU; // faut t'il envoyer ça à ce moment ?
                    }
                    else
                    {
                        coupRep.err =ERR_OK;
                        coupRep.validCoup = VALID;
                        cout<<plateau.afficheTerminal();
                    }
                    if(nbPieceBlanche == 0)
                    {
                        coupRep.propCoup = GAGNE;
                    }
                    else
                    {
                        coupRep.propCoup = CONT;
                    }

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
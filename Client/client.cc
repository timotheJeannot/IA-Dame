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

    TPartieReq req;
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

    TCoul couleur ;
    if(repPartie.validCoulPion == OK)
    {
      couleur = (req.coulPion == BLANC)? BLANC : NOIR;
      cout<<"Vous jouez blanc \n";
    }
    else
    {
      couleur = (req.coulPion == BLANC)? NOIR : BLANC;
      cout<<"Vous jouez noir \n";
    }
    
    

    /************** Début de partie ********************/
    Plateau plateau = Plateau();
    
    while (true)
    {
        cout<<"Etat du plateau :\n"<<plateau.afficheTerminal(); 

        if(couleur == BLANC) // On commence
        {
          
          TCoupReq coup ;
          coup.idRequest = COUP;
          coup.estBloque = false;
          TPion pion ;
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

          TCase c;
          c.l = TNum (y);
          c.c = (TNum) x;

          coup.posPionAv = c;

          Pion p;
          Dame d;
          bool isDame = false;

          if(plateau.getPlateau()[x][y] == 1)
          {
            p = Pion(x,y,true);
          }
          else
          {
              if(plateau.getPlateau()[x][y] == 2)
              {
                d = Dame(x,y,true);
                isDame = true;
              }
              else
              {
                  cerr<<"Les coordonnées choisies ne pointent pas sur une piéce \n";
                  socket.~TcpSocket();
                    return -1;
              }
          }

            int x2,y2;

          //coup.posPionAp = c;
          std::vector<TCase> deplacements;
          if(isDame)
          {
                               
              cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
              cin>>x2;
              cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
              cin>>y2;
              Case cible(x2,y2);
              int retModif= plateau.modifPlateauDeplacementNormal(d, cible);
              TCase cnext;
              cnext.c = (TNum)x2;
              cnext.l = (TNum)y2;
              deplacements.push_back(cnext);
              d.setCase(cible);
              while(retModif == 1)
              {
                  cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
                  cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();                  
                  cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
                  cin>>x2;
                  cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
                  cin>>y2;
                  Case cible(x2,y2);
                  retModif= plateau.modifPlateauDeplacementPrise(d, cible);
                  TCase cnext;
                  cnext.c = (TNum)x2;
                  cnext.l = (TNum)y2;
                  deplacements.push_back(cnext);
                  d.setCase(cible);
              }
              

              plateau.enleverPiecesRafle();

              if(retModif == -1)
              {
                cerr<<"Le coup n'est pas autorisé\n";
                socket.~TcpSocket();
                    return -1;
              }
          }
          else
          {
              cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
              cin>>x2;
              cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
              cin>>y2;
              Case cible(x2,y2);
              int retModif= plateau.modifPlateauDeplacementNormal(p, cible);
              TCase cnext;
              cnext.c = (TNum)x2;
              cnext.l = (TNum)y2;
              deplacements.push_back(cnext);
              p.setCase(cible);
              while(retModif == 1)
              {
                  cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
                  cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();                  
                  cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
                  cin>>x2;
                  cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
                  cin>>y2;
                  Case cible(x2,y2);
                  retModif= plateau.modifPlateauDeplacementPrise(p, cible);
                  TCase cnext;
                  cnext.c = (TNum)x2;
                  cnext.l = (TNum)y2;
                  deplacements.push_back(cnext);
                  p.setCase(cible);

              }
              

              plateau.enleverPiecesRafle();

              if(retModif == -1)
              {
                cerr<<"Le coup n'est pas autorisé\n";
                socket.~TcpSocket();
                    return -1;
              }
          }
          coup.deplacements = deplacements;
          

          packet.is(coup);
          if(gf::SocketStatus::Data != socket.sendPacket(packet))
          {
              cerr<<"erreur lors de l'envoie de coup";
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
              std::vector<TCase> deplacementsAdv = coupAdv.deplacements;
              TCase posPionAvAdv = coupAdv.posPionAv;
              int xAdv = (int) posPionAvAdv.c;
              int yAdv = (int) posPionAvAdv.l;
              Pion pAdv;
              Dame dAdv ;
              bool isDameAdv = false;
              if(plateau.getPlateau()[xAdv][yAdv] == -1)
              {
                pAdv = Pion(xAdv,yAdv,false);
              }
              else
              {
                dAdv = Dame(xAdv,yAdv,false);
                isDameAdv = true;
              }

              int size = deplacementsAdv.size();
              if(isDameAdv)
              {
                for(int i = 0 ; i <size; i++)
                {
                  TCase cnextAdv = deplacementsAdv[i];
                  int x2Adv = (int) cnextAdv.c;
                  int y2Adv = (int) cnextAdv.l;
                  Case cibleAdv(x2Adv,y2Adv);
                  plateau.modifPlateauDeplacementNormal(dAdv,cibleAdv); // ce n'est pas grave si on ne différencie pas les deux types de déplacements, car le serveur à valider le coup

                }
              }
              else
              {
                for(int i = 0 ; i <size; i++)
                {
                  TCase cnextAdv = deplacementsAdv[i];
                  int x2Adv = (int) cnextAdv.c;
                  int y2Adv = (int) cnextAdv.l;
                  Case cibleAdv(x2Adv,y2Adv);
                  plateau.modifPlateauDeplacementNormal(pAdv,cibleAdv); // ce n'est pas grave si on ne différencies pas les deux types de déplacements, car le serveur à valider le coup
                }
              }
              plateau.enleverPiecesRafle();

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
              std::vector<TCase> deplacementsAdv = coupAdv.deplacements;
              TCase posPionAvAdv = coupAdv.posPionAv;
              int xAdv = (int) posPionAvAdv.c;
              int yAdv = (int) posPionAvAdv.l;
              Pion pAdv;
              Dame dAdv ;
              bool isDameAdv = false;
              if(plateau.getPlateau()[xAdv][yAdv] == 1)
              {
                pAdv = Pion(xAdv,yAdv,true);
              }
              else
              {
                dAdv = Dame(xAdv,yAdv,true);
                isDameAdv = true;
              }

              int size = deplacementsAdv.size();
              if(isDameAdv)
              {
                for(int i = 0 ; i <size; i++)
                {
                  TCase cnextAdv = deplacementsAdv[i];
                  int x2Adv = (int) cnextAdv.c;
                  int y2Adv = (int) cnextAdv.l;
                  Case cibleAdv(x2Adv,y2Adv);
                  plateau.modifPlateauDeplacementNormal(dAdv,cibleAdv); // ce n'est pas grave si on ne différencie pas les deux types de déplacements, car le serveur à valider le coup

                }
              }
              else
              {
                for(int i = 0 ; i <size; i++)
                {
                  TCase cnextAdv = deplacementsAdv[i];
                  int x2Adv = (int) cnextAdv.c;
                  int y2Adv = (int) cnextAdv.l;
                  Case cibleAdv(x2Adv,y2Adv);
                  plateau.modifPlateauDeplacementNormal(pAdv,cibleAdv); // ce n'est pas grave si on ne différencies pas les deux types de déplacements, car le serveur à valider le coup
                }
              }
              plateau.enleverPiecesRafle();

            }
          }
          else
          {
            /* la partie est fini, il faut afficher le résultat */
            break;
          }
          

          TCoupReq coup ;
          coup.idRequest = COUP;
          coup.estBloque = false;
          TPion pion ;
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

          TCase c;
          c.l = TNum (y);
          c.c = (TNum) x;

          coup.posPionAv = c;

          Pion p;
          Dame d;
          bool isDame = false;

          if(plateau.getPlateau()[x][y] == -1)
          {
            p = Pion(x,y,false);
          }
          else
          {
              if(plateau.getPlateau()[x][y] == -2)
              {
                d = Dame(x,y,false);
                isDame = true;
              }
              else
              {
                  cerr<<"Les coordonnées choisies ne pointent pas sur une piéce \n";
                  socket.~TcpSocket();
                    return -1;
              }
          }

            int x2,y2;

            

          

          //coup.posPionAp = c;
          std::vector<TCase> deplacements;
          if(isDame)
          {
              cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
              cin>>x2;
              cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
              cin>>y2;
              Case cible(x2,y2);
              int retModif= plateau.modifPlateauDeplacementNormal(d, cible);
              TCase cnext;
              cnext.c = (TNum)x2;
              cnext.l = (TNum)y2;
              deplacements.push_back(cnext);
              d.setCase(cible);
              while(retModif == 1)
              {
                  cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
                  cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();                  
                  cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
                  cin>>x2;
                  cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
                  cin>>y2;
                  Case cible(x2,y2);
                  retModif= plateau.modifPlateauDeplacementPrise(d, cible);
                  TCase cnext;
                  cnext.c = (TNum)x2;
                  cnext.l = (TNum)y2;
                  deplacements.push_back(cnext);
                  d.setCase(cible);
              }
              

              plateau.enleverPiecesRafle();

              if(retModif == -1)
              {
                cerr<<"Le coup n'est pas autorisé\n";
                socket.~TcpSocket();
                    return -1;
              }
          }
          else
          {
              cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
              cin>>x2;
              cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
              cin>>y2;
              Case cible(x2,y2);
              int retModif= plateau.modifPlateauDeplacementNormal(p, cible);
              TCase cnext;
              cnext.c = (TNum)x2;
              cnext.l = (TNum)y2;
              deplacements.push_back(cnext);
              p.setCase(cible);
              while(retModif == 1)
              {
                  cout<<"Vous avez fait une prise et vous devez encore en faire une\n";
                  cout<<"Etat du plateau :\n"<<plateau.afficheTerminal();                  
                  cout<<"Donnez la coordonnée vertical pour le choix de la  future position de la pièce \n";
                  cin>>x2;
                  cout<<"Donnez la coordonnée horizontal pour le choix de la future position de la pièce \n";
                  cin>>y2;
                  Case cible(x2,y2);
                  retModif= plateau.modifPlateauDeplacementPrise(p, cible);
                  TCase cnext;
                  cnext.c = (TNum)x2;
                  cnext.l = (TNum)y2;
                  deplacements.push_back(cnext);
                  p.setCase(cible);
              }
              

              plateau.enleverPiecesRafle();

              if(retModif == -1)
              {
                cerr<<"Le coup n'est pas autorisé\n";
                socket.~TcpSocket();
                    return -1;
              }
          }
          coup.deplacements = deplacements;
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

          auto coupRep = packet.as<TCoupRep>();

          

          
        }
        
    }
    

    // fin de communication
    cout<<"fin de la communication avec le serveur "<<serv<< "sur le port "<<port<<"\n";
     socket.~TcpSocket();
    return 0;
}
#ifndef _PROTO_DAME_H
#define _PROTO_DAME_H

#include <gf/Id.h>
#include <gf/SerializationOps.h>
#include <string>

using namespace gf::literals;

/* Taille des chaines de caracteres pour les noms */
#define T_NOM 30

/* Identificateurs des requetes */
 typedef enum { PARTIE, COUP } IdReq;

/* Types d'erreur */
 typedef enum { ERR_OK,      /* Validation de la requete */
	       ERR_PARTIE,  /* Erreur sur la demande de partie */
	       ERR_COUP,    /* Erreur sur le coup joue */
	       ERR_TYP      /* Erreur sur le type de requete */
} CodeRep;

/* 
 * Structures demande de partie
 */ 
 typedef enum { BLANC, NOIR } Coul;

struct PartieReq{
    static constexpr gf::Id type = "PartieReq"_id;
    IdReq idReq;               /* Identificateur de la requete */
    std::string nomJoueur;      /* Nom du joueur */
    Coul coulPion;             /* Couleur souhaitee du pion */
} ;

template<typename Archive>
  Archive operator|(Archive& ar, PartieReq& data) {
    return ar | data.idReq | data.nomJoueur | data.coulPion;
  }



 typedef enum { OK, KO } ValidCoul;
struct PartieRep{
    static constexpr gf::Id type = "PartieRep"_id;
    CodeRep err;                   /* Code de retour */
    std::string nomAdvers;         /* Nom du joueur adverse */
    ValidCoul validCoulPion;       /* Validation de la couleur pour le pion */
} ;

template<typename Archive>
  Archive operator|(Archive& ar, PartieRep& data) {
    return ar | data.err | data.nomAdvers | data.validCoulPion;
  }


 typedef enum { UN, DEUX, TROIS, QUATRE, CINQ , SIX , SEPT , HUIT , NEUF , DIX } Num;

 struct Case {
 	static constexpr gf::Id type = "Case"_id;
	Num l;           /* Ligne de la position d'un pion */
	Num c;          /* Colonne de la position d'un pion */
};

template<typename Archive>
  Archive& operator|(Archive& ar, Case& data) {
    return ar | data.l | data.c;
  }

/* 
 * Definition de structures pour le placement d'un pion
 */

/* Choix du pion */
 typedef enum { PION , DAME} TypePion;

struct Pion{
	static constexpr gf::Id type = "Pion"_id;
	Coul coulPion;          /* Couleur du pion */
	TypePion typePion;      /* Type du pion joue */
} ;

template<typename Archive>
  Archive& operator|(Archive& ar, Pion& data) {
    return ar | data.coulPion | data.typePion;
  }

/* Propriete des coups */
 typedef enum { CONT, GAGNE, NUL, PERDU } PropCoup;

struct CoupReq{
    static constexpr gf::Id type = "CoupReq"_id;
    IdReq     idRequest;     /* Identificateur de la requete */
    bool      estBloque;     /* Info si le joueur est bloque (vrai) ou non */
    Pion      pion;          /* Info sur le pion joue */
    Case      posPionAv;       /* Position de la case du pion avant le coup */
    Case      posPionAp;	/* Position de la case du pion avant le coup */
    PropCoup  propCoup;      /* Propriete du coup proposee par le joueur */
};

template<typename Archive>
  Archive operator|(Archive& ar, CoupReq& data) {
    return ar | data.idRequest | data.estBloque | data.pion | data.posPionAv | data.posPionAp | data.propCoup ;
  }

/* Validite du coup */
 typedef enum { VALID, TRICHE } ValCoup; // pas de timeout dans un premier temps

/* Reponse a un coup */
struct CoupRep {
    static constexpr gf::Id type = "CoupRep"_id;
    CodeRep  err;            /* Code de retour */
    ValCoup  validCoup;      /* Validite du coup */
    PropCoup propCoup;       /* Propriete du coup validee par l'arbitre */
} ;

template<typename Archive>
  Archive operator|(Archive& ar, CoupRep& data) {
    return ar | data.err | data.validCoup | data.propCoup;
  }


#endif

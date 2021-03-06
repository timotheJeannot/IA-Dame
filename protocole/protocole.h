#ifndef _PROTO_DAME_H
#define _PROTO_DAME_H

#include <gf/Id.h>
#include <gf/SerializationOps.h>
#include <string>
#include <vector>

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
} TCodeRep;

/* 
 * Structures demande de partie
 */

struct TPartieReq{
    static constexpr gf::Id type = "TPartieReq"_id;
    IdReq idReq;               /* Identificateur de la requete */
    std::string nomJoueur;      /* Nom du joueur */
    int  coulPion;             /* Couleur souhaitee du pion */
} ;

template<typename Archive>
  Archive operator|(Archive& ar, TPartieReq& data) {
    return ar | data.idReq | data.nomJoueur | data.coulPion;
  }


struct PartieRep{
    static constexpr gf::Id type = "PartieRep"_id;
    TCodeRep err;                   /* Code de retour */
    std::string nomAdvers;         /* Nom du joueur adverse */
    bool validCoulPion;       /* Validation de la couleur pour le pion */
} ;

template<typename Archive>
  Archive operator|(Archive& ar, PartieRep& data) {
    return ar | data.err | data.nomAdvers | data.validCoulPion;
  }

 struct TCase {
 	static constexpr gf::Id type = "TCase"_id;
	int l;           /* Ligne de la position d'un pion */
	int c;          /* Colonne de la position d'un pion */
};

template<typename Archive>
  Archive& operator|(Archive& ar, TCase& data) {
    return ar | data.l | data.c;
  }

/* 
 * Definition de structures pour le placement d'un pion
 */

/* Choix du pion */
 typedef enum { PION , DAME} TTypePion;

struct TPion{
	static constexpr gf::Id type = "TPion"_id;
	int coulPion;          /* Couleur du pion (1 pour Blanc & -1 pour Noir) */
	TTypePion typePion;      /* Type du pion joue */
} ;

template<typename Archive>
  Archive& operator|(Archive& ar, TPion& data) {
    return ar | data.coulPion | data.typePion;
  }

/* Propriete des coups */
 typedef enum { CONT, GAGNE, NUL, PERDU } TPropCoup;

struct TCoupReq{
    static constexpr gf::Id type = "TCoupReq"_id;
    IdReq     idRequest;     /* Identificateur de la requete */
    bool      estBloque;     /* Info si le joueur est bloque (vrai) ou non */
    TPion      pion;          /* Info sur le pion joue */
    TCase      posPionAv;       /* Position de la case du pion avant le coup */
    std::vector<TCase> deplacements; /*suite de déplacement pour un coup */
    TPropCoup  propCoup;      /* Propriete du coup proposee par le joueur */
};

template<typename Archive>
  Archive operator|(Archive& ar, TCoupReq& data) {
    return ar | data.idRequest | data.estBloque | data.pion | data.posPionAv | data.deplacements | data.propCoup ;
  }

/* Validite du coup */
 typedef enum { VALID, TRICHE } TValCoup; // pas de timeout dans un premier temps

/* Reponse a un coup */
struct TCoupRep {
    static constexpr gf::Id type = "TCoupRep"_id;
    TCodeRep  err;            /* Code de retour */
    TValCoup  validCoup;      /* Validite du coup */
    TPropCoup propCoup;       /* Propriete du coup validee par l'arbitre */
} ;

template<typename Archive>
  Archive operator|(Archive& ar, TCoupRep& data) {
    return ar | data.err | data.validCoup | data.propCoup;
  }


#endif

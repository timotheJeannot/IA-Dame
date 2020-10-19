#ifndef _PROTO_DAME_H
#define _PROTO_DAME_H


/* Taille des chaines de caracteres pour les noms */
#define T_NOM 30

/* Identificateurs des requetes */
typedef enum { PARTIE, COUP } TIdReq;

/* Types d'erreur */
typedef enum { ERR_OK,      /* Validation de la requete */
	       ERR_PARTIE,  /* Erreur sur la demande de partie */
	       ERR_COUP,    /* Erreur sur le coup joue */
	       ERR_TYP      /* Erreur sur le type de requete */
} TCodeRep;

/* 
 * Structures demande de partie
 */ 
typedef enum { BLANC, NOIR } TCoul;

typedef struct {
  TIdReq idReq;               /* Identificateur de la requete */
  char nomJoueur[T_NOM];      /* Nom du joueur */
  TCoul coulPion;             /* Couleur souhaitee du pion */
} TPartieReq;

typedef enum { OK, KO } TValidCoul;
typedef struct {
  TCodeRep err;                   /* Code de retour */
  char nomAdvers[T_NOM];          /* Nom du joueur adverse */
  TValidCoul validCoulPion;       /* Validation de la couleur pour le pion */
} TPartieRep;

typedef enum { UN, DEUX, TROIS, QUATRE, CINQ , SIX , SEPT , HUIT , NEUF , DIX } TNum;

typedef struct {
  TNum l;           /* Ligne de la position d'un pion */
  TNum c;          /* Colonne de la position d'un pion */
} TCase;

/* 
 * Definition de structures pour le placement d'un pion
 */

/* Choix du pion */
typedef enum { PION , DAME} TTypePion;

typedef struct {
  TCoul coulPion;          /* Couleur du pion */
  TTypePion typePion;      /* Type du pion joue */
} TPion;

/* Propriete des coups */
typedef enum { CONT, GAGNE, NUL, PERDU } TPropCoup;

typedef struct {
  TIdReq     idRequest;     /* Identificateur de la requete */
  int        numPartie;     /* Numero de la partie (commencant a 1) */
  bool       estBloque;     /* Info si le joueur est bloque (vrai) ou non */
  TPion      pion;          /* Info sur le pion joue */
  TCase      posPion;       /* Position de la case du pion joue */
  TPropCoup  propCoup;      /* Propriete du coup proposee par le joueur */
} TCoupReq;

/* Validite du coup */
typedef enum { VALID, TRICHE } TValCoup; // pas de timeout dans un premier temps

/* Reponse a un coup */
typedef struct {
  TCodeRep  err;            /* Code de retour */
  TValCoup  validCoup;      /* Validite du coup */
  TPropCoup propCoup;       /* Propriete du coup validee par l'arbitre */
} TCoupRep;


#endif
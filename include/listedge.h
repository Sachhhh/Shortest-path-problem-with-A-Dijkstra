/* --------------------------------------------------
  Fichier listedge.h pour l'implantation du TAD liste chaînée dynamique d'arcs
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _LISTEDGE
#define _LISTEDGE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* --------------------------------------------------
  1. Import du type arc 'edge_t'
-------------------------------------------------- */

#include "edge.h"

/* --------------------------------------------------
  2. Type liste chaînée d’arcs
-------------------------------------------------- */

typedef struct _link {
edge_t val; // ou edge_t* val si on veut faire une liste de pointeurs sur des arcs
struct _link* next;
} link_t, *listedge_t;

/* --------------------------------------------------
  3. Protoype des fonctions realisant les opérations essentielles du type abstrait Liste
-------------------------------------------------- */

/* Crée une liste vide */
listedge_t list_new() ;

/* Retourne VRAI (1) si l est une liste vide */
int list_is_empty(listedge_t l);

/*
  Retourne l'élément en tête de liste
  PRECONDITION : liste non vide
*/
edge_t list_first(listedge_t l);

/* Ajoute l'élément e en tête de la liste et retourne la nouvelle liste */
listedge_t list_add_first(edge_t e, listedge_t l);

/*
  Supprime le maillon en tête de liste et retourne la nouvelle liste
  PRECONDITION : liste non vide
*/
listedge_t list_del_first(listedge_t l);

/* Retourne le nombre d'éléments (ou de maillons) de la liste */
int list_length(listedge_t l);

/*
  Retourne un pointeur sur le premier maillon contenant e,
  ou NULL si e n'est pas dans la liste
*/
listedge_t list_find(edge_t e, listedge_t l);

/* Affiche la liste */
void list_print(listedge_t l);

/* Libère toute la liste et retourne une liste vide */
listedge_t list_delete(listedge_t l);

/* Compte le nombre de e dans la liste */
int list_count(edge_t e, listedge_t l) ;

/* Ajoute en fin de liste */
listedge_t list_add_last(edge_t e, listedge_t l) ;

/* Concatene 2 listes */
listedge_t list_concat(listedge_t l1, listedge_t l2);

/* Clone une liste */
listedge_t list_copy(listedge_t l);

/* Supprime l'element en position n et retourne la nouvelle liste */
listedge_t list_remove_n(int n, listedge_t l) ;

#endif

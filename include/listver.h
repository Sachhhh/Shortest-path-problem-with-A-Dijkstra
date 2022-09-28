/* --------------------------------------------------
  Fichier listver.h pour l'implantation du TAD liste chaînée dynamique de sommets
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _LISTVER_H
#define _LISTVER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* --------------------------------------------------
  1. Import du type arc 'vertex_t'
-------------------------------------------------- */

#include "vertex.h"

/* --------------------------------------------------
  2. Type liste chaînée de sommets
-------------------------------------------------- */

typedef struct _linkver {
vertex_t* val;
struct _linkver* next;
} linkver_t, *listver_t;

/* --------------------------------------------------
  3. Protoype des fonctions realisant les opérations essentielles du type abstrait Liste
-------------------------------------------------- */

/* Crée une liste vide */
listver_t listver_new() ;

/* Retourne VRAI (1) si l est une liste vide */
int listver_is_empty(listver_t l);

/*
  Retourne l'élément en tête de liste
  PRECONDITION : liste non vide
*/
vertex_t* listver_first(listver_t l);

/* Ajoute l'élément e en tête de la liste et retourne la nouvelle liste */
listver_t listver_add_first(vertex_t* e, listver_t l);

/*
  Supprime le maillon en tête de liste et retourne la nouvelle liste
  PRECONDITION : liste non vide
*/
listver_t listver_del_first(listver_t l);

/* Retourne le nombre d'éléments (ou de maillons) de la liste */
int listver_length(listver_t l);

/* Affiche la liste */
void listver_print(listver_t l);

/* Libère toute la liste et retourne une liste vide */
listver_t listver_delete(listver_t l);

/* Ajoute en fin de liste */
listver_t listver_add_last(vertex_t* e, listver_t l) ;

/* Clone une liste */
listver_t listver_copy(listver_t l);


#endif

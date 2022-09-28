/* --------------------------------------------------
  Fichier lifover.h pour l'implantation du TAD pile au moyen d'une liste chaînée dynamique
  @Author : Hugo Brisset, Sacha Heitz
  Created on Mai 2021
---------------------------------------------------*/

#ifndef _LIFOVER_H_
#define _LIFOVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* --------------------------------------------------
  1. On importe le TAD liste d'arcs chaînée dynamique
     On importe le type 'vertex_t'
---------------------------------------------------*/

#include "listver.h"
#include "vertex.h"

/* --------------------------------------------------
  2. Type file de sommets
---------------------------------------------------*/

typedef listver_t lifover_t ;

/* --------------------------------------------------
  3. prototype des fonctions de l'API du TAD Pile
---------------------------------------------------*/

/* Crée et retourne un pile vide ou NULL en cas d'erreur */
lifover_t lifo_new();

/* Supprime le premier element de la pile */
lifover_t lifo_del_first(lifover_t p);

/* Détruit la pile et retourne une pile vide */
lifover_t lifo_delete(lifover_t stack);

/* Retourne 1 si la pile  stack   est vide, 0 sinon */
int lifo_is_empty(lifover_t stack);

/* Ajoute l'élément e à la pile  stack  et retourne la nouvelle pile */
lifover_t lifo_push(vertex_t* e, lifover_t stack);

/*
  Retourne l'élément en tête de pile (sans l'enlever de la pile)
  PRECONDITION : la pile  stack  ne doit pas être vide
*/
vertex_t* lifo_peek(lifover_t stack);

/*
  Enlève l'élément en tête de la pile, et retourne cet élément
  PRECONDITION : la pile pointée par  p_stack  ne doit pas être vide
*/
vertex_t* lifo_pop(lifover_t * p_stack);

/* Détruit la pile et retourne une pile vide */
lifover_t lifo_delete(lifover_t stack);

/* Affiche la pile */
void lifo_print(lifover_t stack);

/* Retourne le nombre d'éléments de la pile */
int lifo_length(lifover_t stack);

/* Renvoie une copie de la pile */
lifover_t lifo_copy(lifover_t l);

/* Renvoie une copie inversée de la pile */
lifover_t lifo_reverse(lifover_t* l);

#endif

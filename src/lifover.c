/* --------------------------------------------------
  Fichier lifover.c pour l'implantation du TAD pile au moyen d'une liste chaînée dynamique
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* --------------------------------------------------
  1. On inclut le fichier des prototypes
-------------------------------------------------- */

#include "listver.h"
#include "lifover.h"

/* --------------------------------------------------
  2. Pour plus de propreté des concepts,
     on définit l'identifier NIL (signifiant "fin de liste")
     plutôt que d'utiliser directement NULL (signifiant "pointeur nul")
-------------------------------------------------- */

#define NIL NULL

/* --------------------------------------------------
  3. On définit les fonctions de traitement des piles de sommets "lifover_t"
-------------------------------------------------- */

/* Crée et retourne un pile vide ou NULL en cas d'erreur */
lifover_t lifo_new(void) {	return NIL; }

/* Retourne 1 si la pile  stack   est vide, 0 sinon */
int lifo_is_empty(lifover_t p) {return listver_is_empty(p); }

/* Ajoute l'élément e à la pile  stack  et retourne la nouvelle pile */
lifover_t lifo_push (vertex_t* e,lifover_t p){
  return listver_add_first(e,p);
}

/* Supprime le premier element de la pile */
lifover_t lifo_del_first(lifover_t p) {
  return listver_del_first(p);
}

/*
  Retourne l'élément en tête de pile (sans l'enlever de la pile)
  PRECONDITION : la pile  stack  ne doit pas être vide
  Attention : la pile n'est pas modifiée
*/
vertex_t* lifo_peek(lifover_t p){
  return listver_first(p) ;
}

/*
  Enlève l'élément en tête de la pile, et retourne cet élément
  PRECONDITION : la pile pointée par  p_stack  ne doit pas être vide
  Attention: la pile est modifiee
*/
vertex_t* lifo_pop(lifover_t* ap){
  vertex_t* temp = lifo_peek(*ap);
  *ap = lifo_del_first(*ap);
  return temp;
}

/* Retourne le nombre d'éléments de la pile */
int lifo_length(lifover_t p) {
  return listver_length(p);
}

/* Affiche la pile */
void lifo_print(lifover_t p) {
  listver_print(p);
}

/* Détruit la pile et retourne une pile vide */
lifover_t lifo_delete(lifover_t p) {
  return listver_delete(p);
}

lifover_t lifo_copy(lifover_t l){
  return listver_copy(l);
}

lifover_t lifo_reverse(lifover_t* l){
  lifover_t reverse = lifo_new();
  int size = lifo_length(*l);
  for (int i=0; i<size; i++){
    reverse = lifo_push(lifo_pop(l),reverse);
  }
  return reverse;
}

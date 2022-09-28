/* --------------------------------------------------
  Fichier listver.c pour l'implantation du TAD liste chaînée dynamique de sommets
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
  1. On inclut le fichier des prototypes
*/

#include "listver.h"

/*
  2. Pour plus de propreté des concepts,
     on définit l'identifier NIL (signifiant "fin de liste")
     plutôt que d'utiliser directement NULL (signifiant "pointeur nul")
*/

#define NIL NULL

/*
  3. On définit les fonctions de traitement des listes de sommets "listver_t"
*/

/* Crée une liste vide */
listver_t listver_new() {
  return NIL;
}

/* Retourne VRAI (1) si l est une liste vide */
int listver_is_empty( listver_t l ) {
  return (NIL == l);
}

/*
  Retourne l'élément en tête de liste
  PRECONDITION : liste non vide
*/
vertex_t* listver_first(listver_t l){
  assert(!listver_is_empty(l));
  return l->val;
}

/* Ajoute l'élément e en tête de la liste et retourne la nouvelle liste */
listver_t listver_add_first( vertex_t* e, listver_t l ) {
  listver_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf(stderr, "Fatal: Unable to allocate new listver link.\n" );
    return l;
  }
  p->val  = e;
  p->next = l;
  return p;
}

/*
  Supprime le maillon en tête de liste et retourne la nouvelle liste
  PRECONDITION : liste non vide
*/
listver_t listver_del_first( listver_t l ) {
  assert(!listver_is_empty(l));

  listver_t p = l->next;
  free(l);
  return p;
}

/* Affiche la liste */
void listver_print(listver_t l) {
  listver_t p;
  printf("(");
  for ( p = l; !listver_is_empty(p); p = p->next) {
    vertex_print(p->val);printf(", ");
  }
  printf(")\n");
}

/* Retourne le nombre d'éléments (ou de maillons) de la liste */
int listver_length(listver_t l) {
  int len = 0;
  listver_t p;
  for( p = l; !listver_is_empty(p) ; p = p->next ) {
    len ++;
  }
  return len;
}

/* Ajoute en fin de liste */
listver_t listver_add_last(vertex_t* e, listver_t l) {
  listver_t ajout;
  listver_t p;
  ajout = listver_new();
  ajout = listver_add_first(e, ajout);

  if (listver_is_empty(l) == 1){return ajout;}

  for (p = l; p->next != NIL; p = p->next){
    continue;
  }
  p->next = ajout;
  return l;
}

/* Libère toute la liste et retourne une liste vide */
listver_t listver_delete(listver_t l) {
  if (listver_is_empty(l) == 1){return l;}
  while (l->next != NIL){
    l = listver_del_first(l);
  }
  free(l);
  l = listver_new();
  return l;
}

/* Clone une liste */
listver_t listver_copy(listver_t l) {
  listver_t clone;
  clone = listver_new();

  if (listver_is_empty(l) == 1){return clone;}

  listver_t p;

  for (p = l; p->next != NIL; p = p->next){
    clone = listver_add_last(p->val, clone);
  }
  clone = listver_add_last(p->val, clone);
  return clone;
}

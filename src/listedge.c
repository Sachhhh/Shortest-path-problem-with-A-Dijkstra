/* --------------------------------------------------
  Fichier listedge.c pour l'implantation du TAD liste chaînée dynamique d'arcs
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
  1. On inclut le fichier des prototypes
*/

#include "listedge.h"

/*
  2. Pour plus de propreté des concepts,
     on définit l'identifier NIL (signifiant "fin de liste")
     plutôt que d'utiliser directement NULL (signifiant "pointeur nul")
*/

#define NIL NULL

/*
  3. On définit les fonctions de traitement des listes d'arcs "listedge_t"
*/

/* Crée une liste vide */
listedge_t list_new() {
  return NIL;
}

/* Retourne VRAI (1) si l est une liste vide */
int list_is_empty( listedge_t l ) {
  return (NIL == l);
}

/*
  Retourne l'élément en tête de liste
  PRECONDITION : liste non vide
*/
edge_t list_first(listedge_t l){
  assert(!list_is_empty(l));
  return l->val;
}

/* Ajoute l'élément e en tête de la liste et retourne la nouvelle liste */
listedge_t list_add_first( edge_t e, listedge_t l ) {
  listedge_t p = calloc( 1, sizeof( *p ) );
  if ( NULL == p ) {
    fprintf(stderr, "Fatal: Unable to allocate new listedge link.\n" );
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
listedge_t list_del_first( listedge_t l ) {
  assert(!list_is_empty(l));

  listedge_t p = l->next;
  free(l);
  return p;
}

/* Affiche la liste */
void list_print(listedge_t l) {
  listedge_t p;
  printf("(");
  for ( p = l; !list_is_empty(p); p = p->next) {
    printf("(%d, %.3lf); ", p->val.arrivee, p->val.cout);
  }
  printf(")\n");
}

/* Retourne le nombre d'éléments (ou de maillons) de la liste */
int list_length(listedge_t l) {
  int len = 0;
  listedge_t p;
  for( p = l; !list_is_empty(p) ; p = p->next ) {
    len ++;
  }
  return len;
}

/*
  Retourne un pointeur sur le premier maillon contenant e,
  ou NULL si e n'est pas dans la liste
*/
listedge_t list_find(edge_t e, listedge_t l){
  listedge_t p;
  for( p = l; !list_is_empty(p) ; p = p->next ){
    if((p->val.arrivee == e.arrivee) && (p->val.cout == e.cout)){
      return p;
    }
  }
  return NULL;
}

/* Compte le nombre de e dans la liste */
int list_count(edge_t e, listedge_t l) {
  int count = 1;
  listedge_t p = l;
  if (list_is_empty(l)){return 0;}
  else{
    while (p->next != NIL){
      if (p->val.arrivee == e.arrivee && p->val.cout == e.cout){count += 1;}
      p = p->next;
    }
  }
  return count;
}

/* Ajoute en fin de liste */
listedge_t list_add_last(edge_t e, listedge_t l) {
  listedge_t ajout;
  listedge_t p;
  ajout = list_new();
  ajout = list_add_first(e, ajout);

  if (list_is_empty(l) == 1){return ajout;}

  for (p = l; p->next != NIL; p = p->next){
    continue;
  }
  p->next = ajout;
  return l;
}

/* Libère toute la liste et retourne une liste vide */
listedge_t list_delete(listedge_t l) {
  if (list_is_empty(l) == 1){return l;}
  while (l->next != NIL){
    l = list_del_first(l);
  }
  free(l);
  l = list_new();
  return l;
}

/* Concatene 2 listes */
listedge_t list_concat(listedge_t l1, listedge_t l2) {
  listedge_t p;
  if (list_is_empty(l2)){return l1;}
  if (list_is_empty(l1)==1){
    l1 = l2;
    return l1;
  }
  for (p = l1; p->next != NIL; p = p->next){
    continue;
  }
  p->next = l2;
  return l1;
}

/* Clone une liste */
listedge_t list_copy(listedge_t l) {
  listedge_t clone;
  clone = list_new();

  if (list_is_empty(l) == 1){return clone;}

  listedge_t p;

  for (p = l; p->next != NIL; p = p->next){
    clone = list_add_last(p->val, clone);
  }
  clone = list_add_last(p->val, clone);
  return clone;
}

/* Supprime l'element en position n et retourne la nouvelle liste */
listedge_t list_remove_n(int n, listedge_t l) {
  if (n <= 0){return l;}
  if (n > list_length(l)){return l;}
  if (n == 1){
    l = list_del_first(l);
    return l;
  }
  int i;
  listedge_t temp;
  listedge_t p = l;
  listedge_t j = l;
  for (i=1 ; i<n; i++){
    p = p->next;
  }
  for (i=1; i<n-1; i++){
    j = j->next;
  }
  j->next = p->next;
  free(p);
  return l;
}

/* --------------------------------------------------
  Fichier edge.c pour l'implantation du TAD edge
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------
  1. On importe le fichier des prototypes
-------------------------------------------------- */

#include "edge.h"

/* --------------------------------------------------
  2. Fonctions realisant les opérations essentielles du type abstrait arc
-------------------------------------------------- */

/* Affiche l'arc */
void edge_print (edge_t e){
  printf("(%d, %.3lf), ", e.arrivee, e.cout);
}

/* Retourne un arc de cout = 0 et d'arrivée = 0 */
edge_t edge_new(){
  edge_t e;
  e.cout = 0;
  e.arrivee= 0;
  return e;
}

/* Retourne VRAI (1) si l'arc est vide */
int edge_is_empty(edge_t e){
  return ((e.cout == 0) && (e.arrivee == 0));
}

/* Compare deux arcs et retourne VRAI (1) si les deux arcs sont identiques, FAUX (0) sinon */
int edge_equal(edge_t edge1, edge_t edge2){
  return  EDGE_EQUAL(edge1, edge2);
}

/*
  Compare deux arcs en fonction de leurs couts
  Retourne 1 si le cout de l'arc 1 est > à celui de l'arc 2
  Retourne 0 si le cout de l'arc 1 et celui de l'arc 2 sont égaux
  Retourne -1 si le cout de l'arc 1 est < à celui de l'arc 2
*/
int edge_compare(edge_t edge1, edge_t edge2){
  return EDGE_COMPARE(edge1, edge2);
}

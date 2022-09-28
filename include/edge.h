/* --------------------------------------------------
  Fichier edge.h pour l'implantation du TAD edge
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _EDGE
#define _EDGE

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------
  1. Type arc 'edge_t'
-------------------------------------------------- */

typedef struct {
int arrivee; // L’indice du sommet d’arrivée de l’arc
double cout; // Le cout (distance) de l’arc
} edge_t;

/* --------------------------------------------------
  2. Fonctions élémentaires
-------------------------------------------------- */

#define EDGE_COMPARE(e1,e2)  ((e1.cout > e2.cout) ? 1 : e1.cout == e2.cout ? 0 : -1)
#define EDGE_EQUAL(e1,e2)  ((e1.arrivee == e2.arrivee) && (e1.cout == e2.cout))

/* --------------------------------------------------
  3. Protoypes des fonctions realisant les opérations essentielles du type abstrait arc
-------------------------------------------------- */

/* Affiche l'arc */
void edge_print (edge_t e);

/* Retourne un arc de cout = 0 et d'arrivée = 0 */
edge_t edge_new();

/* Retourne VRAI (1) si l'arc est vide */
int edge_is_empty(edge_t e);

/* Compare de arcs et retourne VRAI (1) si les deux arcs sont identiques, FAUX (0) sinon */
int edge_equal(edge_t edge1, edge_t edge2);

/*
  Compare deux arcs en fonction de leurs couts
  Retourne 1 si le cout de l'arc 1 est > à celui de l'arc 2
  Retourne 0 si le cout de l'arc 1 et celui de l'arc 2 sont égaux
  Retourne -1 si le cout de l'arc 1 est < à celui de l'arc 2
*/
int edge_compare(edge_t edge1, edge_t edge2);


#endif

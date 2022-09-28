/* --------------------------------------------------
  Fichier tabver.h pour l'implantation de la stucture tableau de pointeurs sur sommet 'tabvert_t'
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _TABVER
#define _TABVER

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"

typedef struct {
  vertex_t** tab; // tableau de pointeurs sur des sommets
  int size; // Nombre d'éléments dans le tableau
} tabver_t;

/* créer un vouveau tabver_t avec 0 éléments dedans */
tabver_t new_tab(int size);

/* Ajouter le nouveau sommet dans l'emplacement correspondant à son indice */
void add_tab(vertex_t* v, tabver_t* t);

/* Ajouter le nouveau sommet dans l'emplacement correspondant à l'indice n */
void add_tab_n(vertex_t* v, tabver_t* t, int n);

#endif

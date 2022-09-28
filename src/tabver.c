/* --------------------------------------------------
  Fichier tabver.c pour l'implantation de la stucture tableau de pointeurs sur sommet 'tabvert_t'
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "tabver.h"

/* créer un vouveau tabver_t avec 0 éléments dedans */
tabver_t new_tab(int size){
  tabver_t t;
  vertex_t** k = calloc(size, sizeof(vertex_t*));
  t.tab = k;
  return t;
}

/* Ajouter le nouveau sommet dans l'emplacement correspondant à son indice */
void add_tab(vertex_t* v, tabver_t* t){
  t->tab[v->numero] = v;
}

/* Ajouter le nouveau sommet dans l'emplacement correspondant à l'indice n */
void add_tab_n(vertex_t* v, tabver_t* t, int n){
  t->tab[n] = v;
}

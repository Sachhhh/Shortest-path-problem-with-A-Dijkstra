/* --------------------------------------------------
  Fichier heap.h pour l'implantation du TAD tas
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _HEAP
#define _HEAP

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------
  1. Import du type sommet 'vertex_t'
-------------------------------------------------- */

#include "vertex.h"

/* --------------------------------------------------
  2. Type Tas de sommets
-------------------------------------------------- */

typedef
  struct {
    vertex_t** data;
    int max_size;
    int number;
  } heap_t;

/* --------------------------------------------------
  3. Protoypes des fonctions realisant les opérations essentielles du type abstrait Tas
-------------------------------------------------- */

/* Crée un Tas vide */
heap_t heap_new(int m);

/* Retourne VRAI (1) si tas est un tas vide */
int heap_is_empty(heap_t tas);

/* Ajoute valeur au tas d'adresse ptas */
int heap_add(vertex_t* valeur, heap_t* ptas);

/* Renvoie l'adresse du sommet de chemin min */
vertex_t* heap_get_min(heap_t tas);

/* Supprime la racine en la remplacant par le dernier element du tas et en réorganisation le tas */
int heap_delete_min(heap_t* ptas);

/*
  Verifie la propriete des tas sur tous les noeuds :
  le pere est plus grand que les 2 fils
*/
int heap_verification(heap_t tas) ;

/* Libere la memoire allouee par heap_new */
void heap_delete(heap_t* ptas);

/* Retourne l'indice du plus petit des deux fils ou -1 si c'est une feuille */
int heap_lowest_son(heap_t tas, int indice);

/* Affiche le tas à l'ecran sous forme linéaire*/
void heap_line_print(heap_t tas) ;

/* Affiche le tas a l'ecran sous forme pyramidale*/
void heap_pyr_print(heap_t tas) ;

/* --------------------------------------------------
  4. Fonctions élémentaires permettant de calculer l'indice du père et des fils d'un élément du Tas
-------------------------------------------------- */

/* Retourne l'indice du père de l'élément d'indice i */
#define HEAP_FATHER(i) (((i)-1)/2)

/* Retourne l'indice du fils gauche de l'élément d'indice i */
#define HEAP_LEFTSON(i) (2*(i)+1)

/* Retourne l'indice du fils droit de l'élément d'indice i */
#define HEAP_RIGHTSON(i) (2*((i)+1))


#endif

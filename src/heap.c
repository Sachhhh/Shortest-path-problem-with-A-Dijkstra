/* --------------------------------------------------
  Fichier heap.c pour l'implantation du TAD tas
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------
  1. On inclut le fichier des prototypes
-------------------------------------------------- */

#include "heap.h"

/* --------------------------------------------------
  2. On définit les fonctions de traitement des listes d'arcs "listedge_t"
-------------------------------------------------- */

/* Crée un Tas vide */
heap_t heap_new(int m) {
  heap_t tas;
  vertex_t** data = calloc(m,sizeof(vertex_t*));
  tas.data = data;
  tas.max_size = m;
  tas.number = 0;
  return tas;
}

/* Retourne VRAI (1) si tas est un tas vide */
int heap_is_empty(heap_t tas) {
  if (tas.number == 0){return 1;}
  else {return 0;}
}

/* Ajoute l'element valeur au tas pointé par ptas */
int heap_add(vertex_t* valeur, heap_t* ptas) {
  // cas ou tas est vide :
  if (heap_is_empty(*ptas) == 1){
    ptas->data[0] = valeur;
    ptas->number += 1;
  }
  else if (ptas->number >= ptas->max_size-1){
    puts("Le Tas est plein\n");
    return -1;
  }
  else {
    int i = ptas->number;
    ptas->number += 1;
    ptas->data[i] = valeur;
    int j = HEAP_FATHER(i);
    vertex_t* pere = ptas->data[j];
    while (valeur->pcc < pere->pcc){
      ptas->data[i] = ptas->data[j];
      ptas->data[j] = valeur;
      i = j;
      j = HEAP_FATHER(j);
      pere = ptas->data[j];
    }
  }
  return 0;
}


/* Retourne l'indice du plus petit des deux fils ou -1 si c'est une feuille */
int heap_lowest_son(heap_t tas, int indice) {
  if (indice >= tas.max_size){
    puts("Indice en dehors du Tas\n");
    return -2;
  }
  else if (indice > tas.number){
    puts("Indice non encore affecté");
    return -2;
  }
  else{
    int l_son_index = HEAP_LEFTSON(indice);
    int r_son_index = HEAP_RIGHTSON(indice);
    if (l_son_index <= tas.number-1 && r_son_index <= tas.number-1){
      vertex_t* l_son = tas.data[l_son_index];
      vertex_t* r_son = tas.data[r_son_index];
      if (l_son->pcc >= r_son->pcc){
        return r_son_index;
      }
      else{
        return l_son_index;
      }
    }
    else if(l_son_index <= tas.number-1 && r_son_index >= tas.number-1){
      return l_son_index;
    }
    else if(l_son_index <= tas.number-1 && r_son_index >= tas.number-1){
      return r_son_index;
    }
  }
  return -1;
}

/* Supprimer la racine en la remplacant par le dernier element du tas et en réorganisant le tas */
int heap_delete_min(heap_t* ptas) {
  ptas -> data[0] = ptas -> data[(ptas->number)-1];
  ptas -> data[(ptas->number)-1] = NULL;
  ptas -> number -= 1;
  int i = 0;
  int lowest_son_index = heap_lowest_son(*ptas, i);
  while (lowest_son_index != -1){
    if (ptas -> data[lowest_son_index]->pcc < ptas -> data[i]->pcc){
      vertex_t* temp_value = ptas -> data[i];
      ptas -> data[i] = ptas -> data[lowest_son_index];
      ptas -> data[lowest_son_index] = temp_value;
      i = lowest_son_index;
    }
    else {
      break;
    }
    lowest_son_index = heap_lowest_son(*ptas, i);
  }
  return 1;
}

/* Libere la memoire allouee par heap_new */
void heap_delete(heap_t* ptas) {
  free(ptas->data);
  ptas->number= 0;
}

/* Retourne le sommet de cout min sans le supprimer du tas */
vertex_t* heap_get_min(heap_t tas) {
  return tas.data[0];
}

/* Affiche le tas a l'ecran sous forme linéaire*/
void heap_line_print(heap_t tas) {
  for (int i=0; i<tas.number; i++){
    if (tas.data[i] != NULL){printf("%d ",tas.data[i]->numero);}
    else{printf("NULL ");}
  }
  puts("");
}

/* Affiche le tas a l'ecran sous forme pyramidale*/
void heap_pyr_print(heap_t tas){
  puts("\n");
  int i = 0;
  int pwr = 1;
  while (i < tas.number){
    for (int a=0; a<pwr; a++){
      if (tas.data[i] != NULL){
        printf("%d ",tas.data[i]->numero);
        i++;
      }
      else{printf("NULL ");}
    }
    puts("\n");
    pwr *= 2;
  }
  puts("---------------------------");
}

/*
  Verifie la propriete des tas sur tous les noeuds :
  le pere est plus petit que les 2 fils
*/
// int heap_verification(heapedge_t tas) {
//   int i;
//   for (i=0; i< tas.number/2; i++) {
//     if (EDGE_COMPARE(tas.data+i,tas.data+HEAP_LEFTSON(i)) == 1) return i;
//     if (HEAP_RIGHTSON(i)<tas.number && tas.data[i]<tas.data[HEAP_RIGHTSON(i)]) return i;
//   }
//   return -1;
// }

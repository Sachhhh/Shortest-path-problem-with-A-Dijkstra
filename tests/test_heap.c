#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "vertex.h"


void main(){

  // création d'un tableau de vertex
  vertex_t* tab = calloc(10,sizeof(vertex_t));
  for (int i=0; i<5; i++){
    vertex_t temp = vertex_new(5-i, "nom", "ligne", 2*i, 3*i, 2*(5-i));
    tab[i] = temp;
  }

  // test heap_new
  heap_t h = heap_new(10);

  // test heap_is_empty
  printf("h est vide ? %d \n",heap_is_empty(h));

  // test heap_add et heap_pyr_print
  for (int i=0; i<5; i++){
    vertex_t* p_ver = &tab[i];
    heap_add(p_ver,&h);
    heap_line_print(h);
    heap_pyr_print(h);
  }

  // test heap_lowest_son
  printf("Lowest son de 1 : %d\n",h.data[heap_lowest_son(h,0)]->numero);
  printf("Lowest son de 2 : %d\n",h.data[heap_lowest_son(h,1)]->numero);
  printf("%d\n",h.number);

  // test heap_delete_min
  int del = heap_delete_min(&h);
  printf("%d\n",h.number);
  heap_pyr_print(h);

  // test heap_get_min
  vertex_t* p_ver2 = heap_get_min(h);
  printf("Le plus petit sommet est : %d\n",p_ver2->numero);

  // test heap_line_print
  heap_line_print(h);
  heap_pyr_print(h);

  // test heap_delete
  heap_delete(&h);
  printf("h vide ? %d \n",heap_is_empty(h));
}

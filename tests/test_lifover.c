#include <stdio.h>
#include <stdlib.h>
#include "lifover.h"
#include "vertex.h"


void main(){
  // création d'un tableau de vertex
  vertex_t* tab = calloc(10,sizeof(vertex_t));
  for (int i=0; i<5; i++){
    vertex_t temp = vertex_new(5-i, "nom", "ligne", 2*i, 3*i, 2*(5-i));
    tab[i] = temp;
    printf("\n"); vertex_print(&temp);
  }
  puts("");

  // Test lifo_new et lifo_push
  lifover_t l = lifo_new();
  for (int i=0; i<5; i++){
    l = lifo_push(&tab[i], l);
  }

  // Test lifo_is_empty et lifo_print
  printf("l est elle vide : %d\n",lifo_is_empty(l));
  lifo_print(l);

  // Test lifo_peek
  vertex_t* k = lifo_peek(l);
  printf("Premier élément de l : ");vertex_print(k);printf("\n");
  lifo_print(l);

  // Test lifo_pop
  vertex_t* m = lifo_pop(&l);
  printf("Premier élément de l : ");vertex_print(m);printf("\n");
  lifo_print(l);

  // Test lifo_length
  printf("La pile fait %d éléments\n",lifo_length(l));

  // Test lifo_delete
  l = lifo_delete(l);
  printf("La pile est elle bien vide après libération : %d\n",lifo_is_empty(l));
}

#include <stdio.h>
#include <stdlib.h>
#include "listver.h"
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

  // Test listver_new et listver_add_first
  listver_t l = listver_new();
  for (int i=0; i<5; i++){
    l = listver_add_first(&tab[i], l);
  }

  // Test listver_is_empty et listver_print
  printf("l est elle vide : %d\n",listver_is_empty(l));
  listver_print(l);

  // Test listver_del_first
  l = listver_del_first(l);
  listver_print(l);

  // Test listver_first
  vertex_t* m = listver_first(l);
  printf("Premier élément de l : ");vertex_print(m);printf("\n");

  // Test listver_lenght
  printf("La liste fait %d éléments\n",listver_length(l));

  // Test listver_delete
  l = listver_delete(l);
  printf("La liste elle est elle bien vide après libération : %d\n",listver_is_empty(l));
}

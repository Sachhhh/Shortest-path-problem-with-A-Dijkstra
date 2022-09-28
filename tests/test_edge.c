#include <stdlib.h>
#include <stdio.h>
#include "edge.h"

void main(){
  // test edge_new
  edge_t e1 = edge_new();

  // test edge_print
  printf("e1 = ");
  edge_print(e1);
  e1.cout = 10; e1.arrivee = 20;
  printf("\ne1 = ");
  edge_print(e1);

  // test edge_is_empty
  edge_t e2 = edge_new();
  printf("\ne2 = ");
  edge_print(e2);
  printf("\ne2 vide ? %d", edge_is_empty(e2));
  e2.cout=2; e2.arrivee = 10;
  printf("\ne2 = ");
  edge_print(e2);
  printf("\ne2 vide ? %d", edge_is_empty(e2));

  // test de edge_equal et edge_compare
  edge_t e3 = edge_new();
  e3.cout = 10; e3.arrivee = 20;
  printf("\ne1 = ");
  edge_print(e1);
  printf("\ne2 = ");
  edge_print(e2);
  printf("\ne3 = ");
  edge_print(e3);
  printf("\ne1 et e2 sont ils égaux ? %d", edge_equal(e1,e2));
  printf("\ne1 et e3 sont ils égaux ? %d", edge_equal(e1,e3));
  printf("\nComparaison de e1 et e2 : %d\n", edge_compare(e1,e2));

}

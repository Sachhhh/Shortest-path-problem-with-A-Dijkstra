#include <stdio.h>
#include <stdlib.h>
#include "listedge.h"
#include "edge.h"


void main(){
  listedge_t mylist = list_new();
  edge_t arc1, arc2;
  arc1 = edge_new();
  arc2 = edge_new();
  arc1.arrivee = 10;
  arc1.cout = 20;
  arc2.arrivee = 50;
  arc2.cout = 2;
  mylist = list_add_first(arc1, mylist);
  mylist = list_add_first(arc2, mylist);
  list_print(mylist);
  int count = 0;
  edge_t e;
  e.arrivee = 10; e.cout = 20;
  count = list_count(e, mylist);
  printf("La liste contient %d fois l'élément (%d %.3lf)\n", count, e.arrivee, e.cout);
  e.arrivee = 200; e.cout = 667;
  edge_print(e); puts(" ");
  mylist = list_add_last(e, mylist);
  list_print(mylist);

  listedge_t list2 = list_new();
  edge_t s3, s4;
  s3.arrivee = 1; s3.cout = 2;
  s4.arrivee = 3; s4.cout = 4;
  list2 = list_add_last(s3, list2);
  list2 = list_add_last(s4, list2);
  list_print(list2);
  mylist = list_concat(mylist, list2);
  list_print(mylist);

  listedge_t clone;
  clone = list_copy(mylist);
  list_print(clone);

  mylist = list_delete(mylist);
  list_print(mylist);

  clone = list_remove_n(2,clone);
  list_print(clone);
}

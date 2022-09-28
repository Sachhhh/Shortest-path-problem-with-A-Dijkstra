#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "graph.h"
#include "lifover.h"

int main(){
  // graph_t graph=Lecture_fichier("/Users/sacha/Downloads/DATA/grapheMonde.txt");
  graph_t graph=Lecture_fichier("/home/hugo/Documents/Phelma/TD_Info/heitzsbrissethprojetS2/DATA_projet2021/grapheMonde.txt");
  Dijkstra(1253,215630,graph,1);
  return 1;
}

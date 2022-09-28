#include "graph.h"

int main(){
  // graph_t graph=Lecture_fichier("/Users/sacha/Downloads/DATA/graphe1.txt");
  graph_t graph=Lecture_fichier("/home/hugo/Documents/Phelma/TD_Info/heitzsbrissethprojetS2/DATA_projet2021/grapheNewYork.txt");
  interface_graphique(graph,"grapheNewYork.txt");
  return(0);
}

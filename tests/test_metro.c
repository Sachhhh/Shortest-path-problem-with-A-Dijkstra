#include "metro.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "Astar.h"
#include "lifover.h"

int main(){
  //graph_t graph=Lecture_fichier("/home/hugo/Documents/Phelma/TD_Info/heitzsbrissethprojetS2/DATA_projet2021/metroetu.txt");
  graph_t graph=Lecture_fichier("/Users/sacha/Downloads/DATA/metroetu.txt");
  char* nomdepart="Asnières-Gennevilliers";
  char* nomarrivee="Gare du Nord";
  //Astar_metro(nomdepart,nomarrivee,graph,"metro",1);
  Dijkstra_metro(nomdepart,nomarrivee,graph,"metro",1);
}

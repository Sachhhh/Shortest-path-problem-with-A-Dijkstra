#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "Astar.h"
#include "Dijkstra.h"

int main(){

  srand(time(NULL));

  int algo;
  char graph_name[512];
  int repeat;
  int depart, arrivee;

  printf("Voulez vous tester Astar ou Dijkstra ? [A/D]\n>> ");
  algo = getchar();
  algo = tolower(algo);
  if ((algo != 'a') && (algo != 'd')){
    printf("Erreur : algorithme non défini\n");
    return EXIT_FAILURE;
  }

  printf("Veuillez saisir l'emplacement du graphe à traiter\n>> ");
  scanf("%s", graph_name);

  printf("Combien de répétitions souhaitez vous faire ?\n>> ");
  scanf("%d", &repeat);

  graph_t graph = Lecture_fichier(graph_name);

  long double sum;
  long double moyenne;

  if (algo == 'a'){
    for (int i=0; i<repeat; i++){
      depart=random()%graph.size_vertices;
      arrivee=random()%graph.size_vertices;
      long double cl = clock();
      Astar(depart, arrivee, graph, 0);
      cl = (clock()-cl)/(long double)CLOCKS_PER_SEC;
      sum += cl;
      printf("Départ : %d, Arrivée : %d, Temps : %.3Lf s\n", depart,arrivee, cl);
    }
    moyenne = (double)sum/repeat;
    printf("Temps moyen d'éxecution d'Astar pour %d répétitions : %.3Lf s\n", repeat, moyenne);
  }

  else if (algo == 'd'){
    for (int i=0; i<repeat; i++){
      depart=random()%graph.size_vertices;
      arrivee=random()%graph.size_vertices;
      long double cl = clock();
      Dijkstra(depart, arrivee, graph, 0);
      cl = (clock()-cl)/(long double)CLOCKS_PER_SEC;
      sum += cl;
      printf("Départ : %d, Arrivée : %d, Temps : %.3Lf s\n", depart,arrivee, cl);
    }
    moyenne = (double)sum/repeat;
    printf("Temps moyen d'éxecution de Dijkstra pour %d répétitions : %.3Lf s\n", repeat, moyenne);
  }

  return EXIT_SUCCESS;
}

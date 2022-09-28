/* --------------------------------------------------
  Fichier vertex.h pour l'implantation de la stucture sommets 'vertex_t'
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "graph.h"
#include "heap.h"
#include "lifover.h"
#include "tabver.h"
#include "listedge.h"


#define INF 999999999
#define HEAPSIZE 100000

/* Initialiser tous les couts et les pcc des sommets du graphe à INF */
void init_vertex_a(graph_t* g);

/* Initialiser le cout et lepcc du sommet de départ à 0 */
void init_depart_a(vertex_t* v);

/* Initialiser l'ensemble atraiter de type Tas */
heap_t init_atraiter_a(int m);

/* Initialiser l'ensemble atteint de type tableau de sommets */
tabver_t init_atteint_a(int size);

/* Calcul la distance estimée (en ligne droite) entre deux sommets */
double heuristique(vertex_t* v1, vertex_t* v2);

/*
  Calculer le plus court chemin entre les sommets départ et arrivee
  au sein du graphe g à l'aide de l'algorithme Dijkstra
*/
int Astar(int depart, int arrivee, graph_t g, int affichage);

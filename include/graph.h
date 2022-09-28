/* --------------------------------------------------
  Fichier graph.h pour l'implantation de la stucture graph_t
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _GRAPH
#define _GRAPH

#include <stdlib.h>
#include <stdio.h>
#include "edge.h"
#include "listedge.h"
#include "vertex.h"
#include "lifover.h"

/* --------------------------------------------------
  1. Type graphe 'graph_t'
-------------------------------------------------- */

typedef struct {
int size_vertices; // nombre de sommets
int size_egdes; // nombre d’arcs
vertex_t* data; // tableau des sommets, alloué dynamiquement
} graph_t;

/* --------------------------------------------------
  2. Définition des constantes
-------------------------------------------------- */

#define WIDTH 1000
#define HIGH 1000

/* --------------------------------------------------
  3. Protoypes des fonctions realisant les opérations essentielles du type abstrait graphe
-------------------------------------------------- */

/* Créer un graphe vide */
graph_t new_graph(int n, int m);

/* Met à jour la liste des arcs partant du sommet n */
void info_edges(graph_t G,int depart,int arrivee,double cout);

/* Renvoie un graphe contenant les données extraites du fichier texte F */
graph_t Lecture_fichier (char* F);

/* Affiche les informations du sommet S */
void Affichage_sommet(vertex_t S);

/* Affiche toutes les donneés du graph */
void Affichage_graph(graph_t graph);

/* Affichage graphique dansune fenêtre du graph à l'aide de la SDL */
int interface_graphique(graph_t g, vertex_t* vdepart, vertex_t* varrivee, lifover_t* pile);


#endif

/* --------------------------------------------------
  Fichier Astar.c pour l'implantation de la recherche du pcc
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
#include "Astar.h"
#include "metro.h"


/* Initialiser tous les couts et les pcc des sommets du graphe à INF */
void init_vertex_a(graph_t* g){
  for (int i=0; i<g->size_vertices; i++){
    g->data[i].cout = INF;
    g->data[i].pcc = INF;
  }
}

/* Initialiser le cout et lepcc du sommet de départ à 0 */
void init_depart_a(vertex_t* v){
  v->cout = 0;
  v->pcc = 0;
}

/* Initialiser l'ensemble atraiter de type Tas */
heap_t init_atraiter_a(int m){
  return heap_new(m);
}

/* Initialiser l'ensemble atteint de type tableau de sommets */
tabver_t init_atteint_a(int size){
  return new_tab(size);
}

/* Calcul la distance estimée (en ligne droite) entre deux sommets */
double heuristique(vertex_t* v1, vertex_t* v2){
  int x1 = v1->x;
  int y1 = v1->y;
  int x2 = v2->x;
  int y2 = v2->y;
  double dist = (abs(x1-x2)+abs(y1-y2))/2;
  return dist;
}

/*
  Calculer le plus court chemin entre les sommets départ et arrivee
  au sein du graphe g à l'aide de l'algorithme Dijkstra
*/
int Astar(int depart, int arrivee, graph_t g, int affichage){

  // Initialisation des variables de départ
  vertex_t* vdepart = &(g.data[depart]); // Pointeur sur le sommet de départ
  vertex_t* varrivee = &(g.data[arrivee]); // Pointeur sur le sommet d'arrivée
  heap_t atraiter = init_atraiter_a(HEAPSIZE); // Tas (ensemble des sommets à traiter)
  tabver_t atteint = init_atteint_a(g.size_vertices); // Tableau de pointeurs sur les sommets déjà atteints
  tabver_t predecesseur = init_atteint_a(g.size_vertices);
  vertex_t* u; // Pointeur sur le sommet actuel que l'on étudie
  vertex_t* v; // Pointeur sur un voisin du sommet qu'on étudie
  double DistTemp; // distance temporaire entre le départ et le sommet qu'on étudie

  // Initialisation du pcc et du cout de chaque sommet
  init_vertex_a(&g);
  init_depart_a(vdepart);

  // Ajout du sommet de départ dans atraiter
  heap_add(vdepart, &atraiter);

  // Tant qu'il reste des sommets à traiter et qu'on a pas la solution
  while (!heap_is_empty(atraiter)){

    // On résupère le sommet a traiter de plus petit cout
    u = heap_get_min(atraiter);
    heap_delete_min(&atraiter);

    // Si c'est le sommet d'arrivée
    if (u == varrivee){

      // On récupère les antécédents dans une pile
      lifover_t path = lifo_new();
      path = lifo_push(varrivee, path);
      vertex_t* tempv = predecesseur.tab[varrivee->numero];
      while (tempv->numero != vdepart->numero){
        path = lifo_push(tempv, path);
        tempv = predecesseur.tab[tempv->numero];
      }
      path = lifo_push(tempv, path);

      // On affiche le résultat unquement si la variable d'affichage vaut 1
      if (affichage == 1){
        // On crée une copie de cette pile pour les deux affichages
        lifover_t cpstack = lifo_copy(path);
        int heap_size = lifo_length(path);
        // Affichage textuel dans le terminal
        printf("Le poids du plus court chemin vaut : %lf\n",u->cout);
        printf("Le plus court chemin pour aller de %d à %d est :\n", depart, arrivee);
        for (int i=0; i<heap_size; i++){
          vertex_t* temp = lifo_pop(&cpstack);
          printf("Le sommet %s numero %d\n", temp->nom, temp->numero);
        }
        interface_graphique(g, vdepart, varrivee, &path);
          // On libère la mémoire allouée
        cpstack = lifo_delete(cpstack);
      }

      // On libère toute la mémoire allouée
      heap_delete(&atraiter);
      free(atteint.tab);
      path = lifo_delete(path);
      for (int i=0; i<g.size_vertices; i++){
        free(g.data[i].ligne);
        free(g.data[i].nom);
        g.data[i].edges = list_delete(g.data[i].edges);
      }
      free(g.data);
      return 1;
    }

    // Si le sommet n'est pas l'arrivée
    else{
      // On ajoute ce sommet aux sommets definitivement atteints
      add_tab(u, &atteint);
      listedge_t cplist = u->edges;
      int list_size = list_length(cplist);

      // On test chacun de ses voisins
      for (int i=0; i<list_size; i++){
        v = g.data+(cplist->val.arrivee);
        DistTemp = u->pcc + cplist->val.cout;
        cplist = cplist->next;
        // On ajoute chaque voisin dans l'ensemble a traiter s'il n'est pas déjà dans atteint
        if ((atteint.tab[v->numero]==NULL) && (DistTemp < v->pcc)){
          v->cout = DistTemp + heuristique(v,varrivee); // On rajoute la prédiction heuristique
          v->pcc = DistTemp;
          add_tab_n(u, &predecesseur, v->numero);
          heap_add(v, &atraiter);
        }
      }
    }
  }

  if (varrivee->cout != INF){
    return 1;
  }
  else {
    printf("Aucun chemin n'a été touvé\n");
    return 0;
  }
}

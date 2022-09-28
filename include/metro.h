/* --------------------------------------------------
  Fichier metro.h pour l'implantation de la recherche du pcc par noms de stations
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */
#include "graph.h"

//Ajoute le ou les numero(s) du sommet dont on donne le nom
void conversion_nom_numero(char* nom,graph_t graph,int numero[]);

// On cherche le plus court chemin entre tous les couples de sommet car un nom peut correspondre à plusieurs sommet
//On garde le plus court de ces chemins et on l'affiche
int Astar_metro(char* nomdepart,char* nomarrivee,graph_t g,char* nom,int affichage);

int Dijkstra_metro(char* nomdepart,char* nomarrivee,graph_t g,char* nom,int affichage);

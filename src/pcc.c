/* --------------------------------------------------
  Fichier ppc.c pour l'implatation du programme permettant de réaliser la recherche
  de pcc à partir des données saisies au clavier par l'utilisateur
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
    -------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "Astar.h"
#include "Dijkstra.h"
#include "metro.h"

int main(){

  // Initialisation des variables des départ
  int type_reseau;
  int algo;
  char graph_name[512];
  int repeat;
  int depart, arrivee;

  // Determination du type de réseau
  printf("Recherche par nom de stations ou par numéro de sommets?\n1:nom\n2:numéro\n>> ");
  type_reseau = getchar();
  type_reseau = tolower(type_reseau);
  if ((type_reseau != '1') && (type_reseau != '2')){
    printf("Erreur : type de réseau non défini\n");
    return EXIT_FAILURE;
  }

  // Lecture du chemin du graphe
  printf("Veuillez saisir l'emplacement du graphe à traiter\n>> ");
  scanf("%s", graph_name);

  // Choix de l'algo de résolution
  printf("Voulez vous utiliser Astar ou Dijkstra ? [A/D]\n>> ");
  getchar();
  algo = getchar();
  algo = tolower(algo);
  if ((algo != 'a') && (algo != 'd')){
    printf("Erreur : algorithme non défini\n");
    return EXIT_FAILURE;
  }

  // S'il s'agit d'un réseau routier
  if (type_reseau == '2'){

    // Lecture du graphe et ecriture en mémoire
    graph_t graph = Lecture_fichier(graph_name);

    // Initialisation des variables
    int size = (graph.size_vertices)-1;
    int depart;
    int arrivee;

    // Determination du sommet de départ
    printf("Veuillez choisir un numéro de sommet de départ (entre 0 et %d)\n>> ",size);
    scanf("%d", &depart);
    if (depart > size){
      printf("Erreur : Ce sommet n'appartient pas au graphe choisi\n");
      return EXIT_FAILURE;
    }

    // Détermination du sommet d'arrivée
    printf("Veuillez choisir un numéro de sommet d'arrivee (entre 0 et %d)\n>> ",size);
    scanf("%d", &arrivee);
    if (arrivee > size){
      printf("Erreur : Ce sommet n'appartient pas au graphe choisi\n");
      return EXIT_FAILURE;
    }

    // Si l'on a choisi l'algo Astar
    if (algo == 'a'){
      Astar(depart, arrivee, graph, 1);
      return EXIT_SUCCESS;
    }

    // S'il on a choisi l'algo Dijkstra
    else if (algo == 'd'){
      Dijkstra(depart, arrivee, graph, 1);
      return EXIT_SUCCESS;
    }
  }

  // S'il s'agit d'un réseau de métro
  else if (type_reseau == '1'){

    // Lecture du graphe et ecriture en mémoire
    graph_t graph = Lecture_fichier(graph_name); // A Remplacer par la lecture des graphes de type métro

    // Initialisation des variables
    int size = (graph.size_vertices)-1;
    char nom_depart[512];
    char nom_arrivee[512];
    int depart, arrivee;

    // Determination du sommet de départ
    printf("Veuillez choisir le nom de la station de départ\n>> ");
    //On utilise fgets plutot que scanf car scanf s'arrête automatiquement s'il y a un espace dans le nom de la station
    getchar();
    fgets(nom_depart,511,stdin);
    if (nom_depart[strlen(nom_depart)-1]<32) nom_depart[strlen(nom_depart)-1]=0;

    // Détermination du sommet d'arrivée
    printf("Veuillez choisir le nom de la station d'arrivée\n>> ");
    //On utilise fgets plutot que scanf car scanf s'arrête automatiquement s'il y a un espace dans le nom de la station
    fgets(nom_arrivee,511,stdin);
    if (nom_arrivee[strlen(nom_arrivee)-1]<32) nom_arrivee[strlen(nom_arrivee)-1]=0;

    // Si l'on a choisi l'algo Astar
    if (algo == 'a'){
      Astar_metro(nom_depart,nom_arrivee,graph,"metro", 1);
      return EXIT_SUCCESS;
    }

    // S'il on a choisi l'algo Dijkstra
    else if (algo == 'd'){
      Dijkstra_metro(nom_depart, nom_arrivee, graph,"metro", 1);
      return EXIT_SUCCESS;
    }
  }
}

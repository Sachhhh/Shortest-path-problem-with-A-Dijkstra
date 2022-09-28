/* --------------------------------------------------
  Fichier graph.c pour l'implantation des stuctures du graph,des sommets et des arcs
  @Author : Hugo Brisset, Sacha Heitz
  Created on Mai 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL_phelma.h>

/* --------------------------------------------------
  1. On importe le fichier des prototypes
-------------------------------------------------- */

#include "listedge.h"
#include "edge.h"
#include "vertex.h"
#include "graph.h"
#include "lifover.h"

/* --------------------------------------------------
  2.  Fonctions realisant les opérations sur les graphes, sommets et arcs
-------------------------------------------------- */

/* Création d'une nouvelle entité 'graph_t' */
graph_t new_graph(int n, int m){
  graph_t G;
  vertex_t sommet;
  listedge_t l=list_new();
  char c;
  sommet.ligne=calloc(10,sizeof(c));
  sommet.nom=calloc(20,sizeof(c));
  sommet.edges=l;
  G.data=calloc(n,sizeof(sommet));
  //On verifie que l'allocation a fonctionné
  if(G.data!=NULL){
    G.size_vertices=n;
    G.size_egdes=m;
    int i;
    for (i = 0; i < n; i++) {
      G.data[i]=sommet;
    }
    return G;
  }
  //On traite le cas ou G.data==NULL
  else{
    printf("Erreur d'allocation du graphe\n");
    exit(EXIT_FAILURE);
  }
}

/* Mise à jour de la liste des arcs partant d'un sommet */
void info_edges(graph_t G,int depart,int arrivee,double cout){
  edge_t e;
  e.arrivee=arrivee;
  e.cout=cout;
  //On ajoute l'élément e à la liste de sommet correspondant
  G.data[depart].edges=list_add_first(e,G.data[depart].edges);
}

/* Remplissage d'une structure 'graph_t' à partir d'un fichier .txt */
graph_t Lecture_fichier (char* F){
  FILE* f;
  f=fopen(F,"r");
  if (f==NULL) {
    printf("Impossible d’ouvrir le fichier\n");
    exit(EXIT_FAILURE);
  }
  int numero,nbsommet,nbarc;
  long double pcc=0.0;
  char line[512];
  char nom[512];
  int depart,arrivee;
  double cout,lat,longi;

  //On crée un graph de la bonne taille
  fscanf(f,"%d %d ",&nbsommet,&nbarc);
  graph_t graph=new_graph(nbsommet,nbarc);
  fgets(nom,511,f);
  int i;

  //On ajoute les sommets au graph
  for (i=0; i < nbsommet; i++ ) {
    fscanf(f,"%d %lf %lf %s",&numero,&lat,&longi,line);
    // printf("%d\n",numero);
    // printf("%lf\n",longi);
    fgets(nom,511,f);
    if (nom[strlen(nom)-1]<32) nom[strlen(nom)-1]=0;
    while (nom[0]=='\t' || nom[0]==' '){
      memmove(nom,nom+1,strlen(nom));
    }
    info_vertex(graph.data+i,numero,line,lat,longi,nom,pcc);
    // printf("%s\n",graph.data[i].nom);
  }
  fgets(nom,511,f);

    //on ajoute les arcs au graph
  for(i=0;i<nbarc;i++){
    fscanf(f,"%d %d %lf",&depart,&arrivee,&cout);
    info_edges(graph,depart,arrivee,cout);
    fgets(nom,511,f);
  }

  fclose(f);
  return(graph);
}

/* Affiche les informations du sommet S */
void Affichage_sommet(vertex_t S){
  printf("Numéro du sommet : %d\n",S.numero);
  printf("Nom du sommet : %s\n",S.nom);
  printf("Ligne du Sommet : %s\n",S.ligne);
  printf("Latitude du sommet : %lf\n",S.x);
  printf("Longitude du sommet : %lf\n",S.y);
  printf("Cout du sommet : %Lf\n",S.pcc);
  list_print(S.edges);
}

/* Affiche toutes les donneés du graph */
void Affichage_graph(graph_t graph){
  printf("Nombre de sommet : %d\n",graph.size_vertices );
  printf("Nombre d'arcs : %d\n",graph.size_egdes);
  int i;
  for (i = 0; i < graph.size_vertices; i++) {
    printf("Sommet : %d\n",i);
    Affichage_sommet(graph.data[i]);
  }
}

/* Affichage graphique dansune fenêtre du graph à l'aide de la SDL */
int interface_graphique(graph_t g, vertex_t* vdepart, vertex_t* varrivee, lifover_t* pile){
  // initialisation de la fenêtre graphique et des variables
  SDL_PHWindow* window;

  // définition des différentes couleurs utilisés pour afficher les grap
  unsigned int edge_color=SDL_PH_GREEN;
  unsigned int color_M1 = SDL_PH_GREEN;
  unsigned int color_M2 = 4285163365;
  unsigned int color_M3 =4280245565;
  unsigned int color_M3bis = 4290864284;
  unsigned int color_M4 = 4283988130;
  unsigned int color_M5 = 4279843696;
  unsigned int color_M6 = 4293410336;
  unsigned int color_M7 =SDL_PH_YELLOW;
  unsigned int color_M7bis =4289442879;
  unsigned int color_M8 =4290078104;
  unsigned int color_M9 =4279854395;
  unsigned int color_M10 =4285378922;
  unsigned int color_M11 =4282913104;
  unsigned int color_M12 =4286687863;
  unsigned int color_M13 =4292791591;
  unsigned int color_M14 =4289442879;
  unsigned int color_funi_val = SDL_PH_CYAN;
  unsigned int color_A =4293410336;
  unsigned int color_B =SDL_PH_MAGENTA;
  unsigned int color_C =SDL_PH_BLUE;
  unsigned int color_D =SDL_PH_GREEN;
  unsigned int color_E =SDL_PH_CYAN;
  unsigned int color_T =SDL_PH_RED;
  unsigned int vertex_color = SDL_PH_BLACK;
  unsigned int path_color = SDL_PH_BLACK;
  double x1, y1, x2, y2;
  int index_x2;

  // Création de la fenêtre
  window = SDL_PH_CreateWindow(WIDTH,HIGH);
  if (window == NULL) {printf("Erreur : Impossible de créer la fenêtre graphique\n"); return EXIT_FAILURE;}

  // Calcul des bornes de variation des coordonnées
  double max_x, min_x, max_y, min_y;
  max_x = g.data[0].x; min_x = g.data[0].x;
  max_y = g.data[0].y; min_y = g.data[0].y;
  for (int i=1; i<g.size_vertices; i++){
    if (g.data[i].x > max_x){max_x = g.data[i].x;}
    else if (g.data[i].x < min_x){min_x = g.data[i].x;}
    if (g.data[i].y > max_y){max_y = g.data[i].y;}
    else if (g.data[i].y < min_y){min_y = g.data[i].y;}
  }
  double delta_x = (max_x - min_x);
  double delta_y = max_y - min_y;

  for (int i=0; i<g.size_vertices; i++){
    g.data[i].x = (((g.data[i].x)-min_x)/delta_x)*(0.9*WIDTH) + 0.05*WIDTH;
    g.data[i].y = abs(((((g.data[i].y)-min_y)/delta_y)*(0.9*HIGH) + 0.05*HIGH)-HIGH);
  }

  // Affichage des arcs un par un
  for (int i=0; i<g.size_vertices; i++){
    // On crée une copie de la liste des arcs voisins pour pouvoir la lire maillon par maillon
    listedge_t edges_cp = g.data[i].edges;
    for (int j=0; j<list_length(g.data[i].edges); j++){
      // Calcul des coordonnées des deux points sommets dans la fenêtre
      x1 = g.data[i].x;
      y1 = g.data[i].y;
      index_x2 = edges_cp->val.arrivee;
      edges_cp = edges_cp->next;
      x2 = g.data[index_x2].x;
      y2 = g.data[index_x2].y;
      // Tracé de l'arc
      if(strcmp((g.data[i].ligne),"M1")==0){edge_color=color_M1;}
      else if(strcmp((g.data[i].ligne),"M2")==0){edge_color=color_M2;}
      else if(strcmp((g.data[i].ligne),"M3")==0){edge_color=color_M3;}
      else if(strcmp((g.data[i].ligne),"M3bis")==0){edge_color=color_M3bis;}
      else if(strcmp((g.data[i].ligne),"M4")==0){edge_color=color_M4;}
      else if(strcmp((g.data[i].ligne),"M5")==0){edge_color=color_M5;}
      else if(strcmp((g.data[i].ligne),"M6")==0){edge_color=color_M6;}
      else if(strcmp((g.data[i].ligne),"M7")==0){edge_color=color_M7;}
      else if(strcmp((g.data[i].ligne),"M7bis")==0){edge_color=color_M7bis;}
      else if(strcmp((g.data[i].ligne),"M8")==0){edge_color=color_M8;}
      else if(strcmp((g.data[i].ligne),"M9")==0){edge_color=color_M9;}
      else if(strcmp((g.data[i].ligne),"M10")==0){edge_color=color_M10;}
      else if(strcmp((g.data[i].ligne),"M11")==0){edge_color=color_M11;}
      else if(strcmp((g.data[i].ligne),"M12")==0){edge_color=color_M12;}
      else if(strcmp((g.data[i].ligne),"M13")==0){edge_color=color_M13;}
      else if(strcmp((g.data[i].ligne),"M14")==0){edge_color=color_M14;}
      else if(strcmp((g.data[i].ligne),"funi_val")==0){edge_color=color_funi_val;}
      else if(strcmp((g.data[i].ligne),"A")==0){edge_color=color_A;}
      else if(strcmp((g.data[i].ligne),"B")==0){edge_color=color_B;}
      else if(strcmp((g.data[i].ligne),"C")==0){edge_color=color_C;}
      else if(strcmp((g.data[i].ligne),"D")==0){edge_color=color_D;}
      else if(strcmp((g.data[i].ligne),"E")==0){edge_color=color_E;}
      else if(strcmp((g.data[i].ligne),"T")==0){edge_color=color_T;}
      lineColor(window->rendu, x1, y1, x2, y2, edge_color);
    }
  }
  // Mise à jour de la fenêtre avec les arcs
  SDL_PH_FlushWindow(window);

  // Test de la taille du graphe par rapport à la fenêtre
  if (g.size_vertices < 0.01*HIGH*WIDTH){
    // Affichage des sommets un par un
    for (int i=0; i<g.size_vertices; i++){
      filledCircleColor(window->rendu, (g.data[i].x)*WIDTH/3, (g.data[i].y)*HIGH/50, 2, vertex_color);
    }
    // Mise à jour de la fenêtre avec les points
    SDL_PH_FlushWindow(window);
  }


  // Affichage du chemin le plus court
  int size = lifo_length(*pile);
  vertex_t* temp1 = lifo_pop(pile);
  vertex_t* temp2;
  for (int i=1; i<size; i++){
    temp2 = lifo_pop(pile);
    x1 = temp1->x;
    y1 = temp1->y;
    x2 = temp2->x;
    y2 = temp2->y;
    // Tracé de l'arc
    lineColor(window->rendu, x1, y1, x2, y2, path_color);
    temp1 = temp2;
  }
  // Mise à jour de la fenêtre avec le pcc
  SDL_PH_FlushWindow(window);

  getchar();
  getchar();
  SDL_PH_DestroyWindow(window); SDL_Quit();
  return EXIT_SUCCESS;
}

/* --------------------------------------------------
  Fichier metro.h pour l'implantation de la recherche du pcc par noms de stations
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */
#include "graph.h"
#include "metro.h"
#include <string.h>
#include "Astar.h"


void conversion_nom_numero(char* nom,graph_t graph,int numero[]){
  int i=0;
  int j=0;
  while( i < graph.size_vertices) {
    if(strcmp((graph.data[i].nom),nom)==0){
       numero[j]=i;
       j++;
  }
  i++;
}
}

int Astar_metro(char* nomdepart,char* nomarrivee,graph_t g,char* nom,int affichage){
  // Initialisation des variables de départ
  vertex_t* vdepart; // Pointeur sur le sommet de départ
  vertex_t* varrivee; // Pointeur sur le sommet d'arrivée
  vertex_t* u; // Pointeur sur le sommet actuel que l'on étudie
  vertex_t* v; // Pointeur sur un voisin du sommet qu'on étudie
  double DistTemp; // distance temporaire entre le départ et le sommet qu'on étudie
  int i=0;
  long double cout_min=INF;
  lifover_t path = lifo_new();
  int Liste_depart[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int Liste_arrivee[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  //On determine le ou les sommets correspondant(s) aux noms de départ et d'arrivée
  (conversion_nom_numero(nomdepart,g,Liste_depart));
  (conversion_nom_numero(nomarrivee,g,Liste_arrivee));
  if (Liste_depart[0]==-1) {
    printf("Aucun sommet de départ trouvé\n");
    EXIT_FAILURE;}
  if (Liste_arrivee[0]==-1) {
    printf("Aucun sommet d'arrivée trouvé\n");
    EXIT_FAILURE;}
    //On cherche les plus courts chemins pour chaque couple de sommet
   while(Liste_depart[i]!=-1){
     int depart=Liste_depart[i];
     int j=0;
     while(Liste_arrivee[j]!=-1){
       heap_t atraiter = init_atraiter_a(HEAPSIZE); // Tas (ensemble des sommets à traiter)
       tabver_t atteint = init_atteint_a(g.size_vertices); // Tableau de pointeurs sur les sommets déjà atteints
       tabver_t predecesseur = init_atteint_a(g.size_vertices);
       int arrivee=Liste_arrivee[i];
       vdepart = &(g.data[depart]); // Pointeur sur le sommet de départ
       varrivee = &(g.data[arrivee]); // Pointeur sur le sommet d'arrivée

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
            //Si le nouveau chemin est plus rapide
           if(cout_min>u->cout){
              cout_min=u->cout;
            // On récupère les antécédents dans une pile
            path = lifo_push(varrivee, path);
            vertex_t* tempv = predecesseur.tab[varrivee->numero];
            while (tempv->numero != vdepart->numero){
              path = lifo_push(tempv, path);
              tempv = predecesseur.tab[tempv->numero];
            }
            path = lifo_push(tempv, path);
          }
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
        heap_delete(&atraiter);
        free(atteint.tab);
        j++;
    }
  i++;
}
if (cout_min != INF){
  // On affiche le résultat unquement si la variable d'affichage vaut 1
  if (affichage == 1){
    // On crée une copie de cette pile pour les deux affichages
    lifover_t cpstack = lifo_copy(path);
    int heap_size = lifo_length(path);
    // Affichage textuel dans le terminal
    printf("Le poids du plus court chemin vaut : %Lf\n",cout_min);
    printf("Le plus court chemin pour aller de %s à %s est :\n", nomdepart, nomarrivee);
    for (int i=0; i<heap_size; i++){
      vertex_t* temp = lifo_pop(&cpstack);
      printf("%s %s \n", g.data[temp->numero].ligne,temp->nom);
    }
    // Affichage Graphique de la carte et de la solution
    interface_graphique(g, vdepart, varrivee, &path);

    // On libère la mémoire allouée
    cpstack = lifo_delete(cpstack);
  }
  if (cout_min != INF){
    // On affiche le résultat unquement si la variable d'affichage vaut 1
    if (affichage == 1){
      // On crée une copie de cette pile pour les deux affichages
      lifover_t cpstack = lifo_copy(path);
      int heap_size = lifo_length(path);
      // Affichage textuel dans le terminal
      printf("Le poids du plus court chemin vaut : %Lf\n",cout_min);
      printf("Le plus court chemin pour aller de %s à %s est :\n", nomdepart, nomarrivee);
      for (int i=0; i<heap_size; i++){
        vertex_t* temp = lifo_pop(&cpstack);
        printf("Le sommet %s numero %d\n", temp->nom, temp->numero);
      }
      // Affichage Graphique de la carte et de la solution
      interface_graphique(g, vdepart, varrivee, &path);

      // On libère la mémoire allouée
      cpstack = lifo_delete(cpstack);
    }
    // On libère toute la mémoire allouée
    path = lifo_delete(path);
    return 1;
  }
  else {
    printf("Aucun chemin n'a été touvé\n");
    return 0;
  }
  }
}

  int Dijkstra_metro(char* nomdepart,char* nomarrivee,graph_t g,char* nom,int affichage){
  // Initialisation des variables de départ
  vertex_t* vdepart; // Pointeur sur le sommet de départ
  vertex_t* varrivee; // Pointeur sur le sommet d'arrivée
  vertex_t* u; // Pointeur sur le sommet actuel que l'on étudie
  vertex_t* v; // Pointeur sur un voisin du sommet qu'on étudie
  double DistTemp; // distance temporaire entre le départ et le sommet qu'on étudie
  int i=0;
  long double cout_min=INF;
  lifover_t path = lifo_new();
  int Liste_depart[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int Liste_arrivee[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  (conversion_nom_numero(nomdepart,g,Liste_depart));
  (conversion_nom_numero(nomarrivee,g,Liste_arrivee));
  if (Liste_depart[0]==-1) {
    printf("Aucun sommet de départ trouvé\n");
    EXIT_FAILURE;}
  if (Liste_arrivee[0]==-1) {
    printf("Aucun sommet d'arrivée trouvé\n");
    EXIT_FAILURE;}
   while(Liste_depart[i]!=-1){
     int depart=Liste_depart[i];
     int j=0;
     while(Liste_arrivee[j]!=-1){
       heap_t atraiter = init_atraiter_a(HEAPSIZE); // Tas (ensemble des sommets à traiter)
       tabver_t atteint = init_atteint_a(g.size_vertices); // Tableau de pointeurs sur les sommets déjà atteints
       tabver_t predecesseur = init_atteint_a(g.size_vertices);
       int arrivee=Liste_arrivee[i];
       vdepart = &(g.data[depart]); // Pointeur sur le sommet de départ
       varrivee = &(g.data[arrivee]); // Pointeur sur le sommet d'arrivée

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

          // Si c'est le sommet d'arrivée et que le nouveau chemin est plus rapide
          if (u == varrivee){
           if(cout_min>u->cout){
              cout_min=u->cout;
            // On récupère les antécédents dans une pile
            path = lifo_push(varrivee, path);
            vertex_t* tempv = predecesseur.tab[varrivee->numero];
            while (tempv->numero != vdepart->numero){
              path = lifo_push(tempv, path);
              tempv = predecesseur.tab[tempv->numero];
            }
            path = lifo_push(tempv, path);
          }
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
                v->cout = DistTemp;
                v->pcc = DistTemp;
                add_tab_n(u, &predecesseur, v->numero);
                heap_add(v, &atraiter);
              }
            }
          }
        }
        heap_delete(&atraiter);
        free(atteint.tab);
        j++;
    }
  i++;
}
if (cout_min != INF){
  // On affiche le résultat unquement si la variable d'affichage vaut 1
  if (affichage == 1){
    // On crée une copie de cette pile pour les deux affichages
    lifover_t cpstack = lifo_copy(path);
    int heap_size = lifo_length(path);
    // Affichage textuel dans le terminal
    printf("Le poids du plus court chemin vaut : %Lf\n",cout_min);
    printf("Le plus court chemin pour aller de %s à %s est :\n", nomdepart, nomarrivee);
    for (int i=0; i<heap_size; i++){
      vertex_t* temp = lifo_pop(&cpstack);
      printf("%s %s \n", g.data[temp->numero].ligne,temp->nom);
    }
    // Affichage Graphique de la carte et de la solution
    interface_graphique(g, vdepart, varrivee, &path);

      // On libère la mémoire allouée
      cpstack = lifo_delete(cpstack);
    }
    // On libère toute la mémoire allouée
    path = lifo_delete(path);
    return 1;
  }
  else {
    printf("Aucun chemin n'a été touvé\n");
    return 0;
  }
}

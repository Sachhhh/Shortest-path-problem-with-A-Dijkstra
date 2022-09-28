/* --------------------------------------------------
  Fichier vertex.h pour l'implantation de la stucture sommets 'vertex_t'
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _VERTEX
#define _VERTEX

#include <stdlib.h>
#include <stdio.h>
#include "edge.h"
#include "listedge.h"

/* --------------------------------------------------
  1. Type sommet 'vertex_t'
-------------------------------------------------- */

typedef struct {
  int numero; // indice du sommet
  char* nom;// nom donné au sommet
  char* ligne; // nom de la ligne, utile uniquement pour le métro
  double x,y; // coordonnées latitude et longitude du sommet
  listedge_t edges; // liste des arcs qui partent de ce sommet
  long double pcc; // valeur du "plus court chemin" entre le sommet de départ et ce sommet
  double cout; // Le cout pour se rendre du sommet ou l'on se trouve à ce sommet
} vertex_t;

/* --------------------------------------------------
  2. Protoypes des fonctions realisant les opérations essentielles du type abstrait sommet
-------------------------------------------------- */

void info_vertex(vertex_t* v,int numero,char* ligne,double x,double y,char* nom,double pcc);

vertex_t vertex_new(int numero, char* nom, char* ligne, double x, double y, double pcc);

void vertex_print(vertex_t* v);

#endif

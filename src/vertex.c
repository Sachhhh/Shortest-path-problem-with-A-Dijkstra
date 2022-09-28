/* --------------------------------------------------
  Fichier vertex.c pour l'implantation de la stucture sommets 'vertex_t'
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------------------------
  1. On importe le fichier des prototypes
-------------------------------------------------- */

#include "vertex.h"

/* --------------------------------------------------
  2. Protoypes des fonctions realisant les opérations essentielles du type abstrait sommet
-------------------------------------------------- */
void info_vertex(vertex_t* v,int numero,char* ligne,double x,double y,char* nom,double pcc){
  v->numero=numero;
  v->ligne=strdup(ligne);
  v->x=x;
  v->y=y;
  v->pcc=pcc;
  v->nom=strdup(nom);}

vertex_t vertex_new(int numero, char* nom, char* ligne, double x, double y, double pcc){
  vertex_t v;
  v.numero=numero;
  v.ligne=strdup(ligne);
  v.x=x;
  v.y=y;
  v.pcc=pcc;
  v.nom=strdup(nom);
  return v;
}

void vertex_print(vertex_t* v){
  printf("(Sommet %s; N°%d; Coordonnées : %.3lf, %.3lf; Pcc : %.3Lf)",v->nom, v->numero, v->x, v->y, v->pcc);
}

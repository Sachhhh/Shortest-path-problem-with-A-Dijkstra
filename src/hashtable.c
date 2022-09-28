/* --------------------------------------------------
  Fichier hashtable.c
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* --------------------------------------------------
  1. On inclut le fichier des prototypes
-------------------------------------------------- */

#include "hashtable.h"

/*---------------------------------------------------
  2. On définit des constantes
-------------------------------------------------- */

#define M 1000
#define A 31

/* --------------------------------------------------
  3. On définit les fonctions de traitement des table de hash "hashtable.c"
-------------------------------------------------- */

/* Fonction de hashage */
unsigned int hash(char* s, int n) {
  int i ;
  int multiplieur = 1 ; //sert a stocker le mutliple de 31
  unsigned int compteur = s[0] ;
  for(i=1 ; s[i] != '\0' ; i++ ) {
    multiplieur *= A ; //on rajoute la puissance
    compteur += (tolower(s[i])*multiplieur) ;
  }
  //on applique le modulo
  compteur = compteur %n ;

  return compteur;
}

/* crée et retourne une nouvelle table de m listes vides */
hashtable_t hashtable_new(int m) {
  hashtable_t tab; //creation de la liste
  tab.size = m ;
  tab.data = calloc (m ,sizeof(listedge_t)) ; //allocution dynamique de la liste

  int i ;
  for (i=0 ; i<m ; i++) {
    tab.data[i] = list_new() ;
  }
  return tab;
}

/*
  Associe la valeur   v   a la clé   k   dans la table t.
  Si la clé   k   n'est pas encore dans la table, ajoute le couple [clé k , valeur v] à la table.
  Si la clé   k   est déjà présente dans la table, alors change la valeur associée à cette clé
  Retourne 1 si réussi, 0 sinon
*/
int hashtable_put(keys_t k, value_t v, hashtable_t t) {
  //cas ou k n'est pas dans la table
  unsigned int index = hash(k,t.size);
  if (list_is_empty(t.data[index]) == 1)  {
    //l'element va etre ajoute dans t.data[v]
    //creation de l'element
    edge_t ajout = edge_new(k,v) ;

    //ajout de l'element a la liste
    t.data[index] = list_add_first(ajout, t.data[index]) ;

    return 1 ;
  }

  //cas ou k est pas dans la table
  if (list_is_empty(t.data[index]) == 0)  {
    if (hashtable_contains_key(k,t)==1) {
    list_t p ;
    for (p = t.data[index] ; p != NULL ; p = p->next ) {
      if (key_equal(p -> val.key , k) == 1) {
        p -> val.value = v ;
        return 1 ;
      }
    }
  }

  //l'element va etre ajoute dans t.data[v] a la fin de la liste
  //creation de l'element
  edge_t ajout = edge_new(k,v) ;

  //ajout de l'element a la liste
  t.data[v] = list_add_last(ajout, t.data[v]) ;

  return 1 ;
}
//si on arrive ici il y a eu un pb
return 0;
}

/* retourne 1 (true) si la clé k existe dans la table, 0 sinon */
int hashtable_contains_key(keys_t k,hashtable_t t) {
  //on obtient la valeur la longueur de la liste pour pouvoir calculer la table de hachage
  unsigned int valeur = hash(k,t.size) ;

  if (list_is_empty(t.data[valeur]) == 1 ) return 0 ;

    list_t p ;
    for (p = t.data[valeur] ; p != NULL ; p = p -> next) {
      if (key_equal(k,p -> val.key) == 1) return 1 ;
    }

    return 1 ;
  }

/*
  Trouve et retourne la valeur associee à la cle k dans la table.
  Si la clé est présente, remplit la variable pointée par pv avec la valeur de la clé et retourne 1.
  Si la clé n'est pas présente, retourne 0.
*/
int hashtable_get_value(keys_t k, value_t* pv, hashtable_t t) {
  //on obtient le hashcode
  unsigned int code = hash(k,t.size) ;

  //on cree une list_t qui pointera sur la valeur a trouver (ou sur NULL si elle n'y est pas)
  list_t l = list_new ();
  l = list_find_key(k,t.data[code]) ;
  if (l==NULL) return 0 ;
  *pv = ((*l).val).value ; //on aurait aussi pu prendre code
  return 1 ;//*pv
}

/* supprime la clé k et la valeur associée de la table t retourne 1 si la suppression est réalisée, 0 sinon */
int hashtable_delete_key(keys_t k, hashtable_t t) {
  //verifions si cette cle est presente
  value_t code ;
  if (hashtable_get_value(k , &code , t ) == 0 ){
    printf("Le mot %s n'est pas dans la table\n",k);
    return 0 ;
 }

  unsigned int valeur = hash(k,t.size) ;

  //si c'est bon, code a une valeur
  t.data[valeur] = list_delete_key(k,t.data[valeur]) ;

  return 0;
}

/* supprime tous les éléments, détruit la table et retourne une table vide */
hashtable_t hashtable_delete(hashtable_t t) {
  int i ;
  for (i=0 ; i<t.size ; i++ ) t.data[i] = list_delete(t.data[i]) ;
  free (t.data) ;

  return t;
}

/* Affiche toutes les paires [cle, valeur] contenues dans la table */
void hashtable_print(hashtable_t t) {
  //2 compteurs, une longueur
  int i ;

  printf("Taille : %d\n", t.size );
  puts("La table est la suivante :");
  for (i=0 ; i< t.size ; i++) {
    list_t p  ;
    for (p= t.data[i] ; p != NULL ; p = p -> next ) {
      element_print(p -> val) ; printf("\n" );
    }
  }
}

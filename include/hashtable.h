/* --------------------------------------------------
  Fichier hashtable.h pour l'implantation du TAD table de hash
  @Author : Hugo Brisset, Sacha Heitz
  Created on April 2021
-------------------------------------------------- */

#ifndef _HASHTABLE
#define _HASHTABLE

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------
  1. On importe le TAD liste d'arcs chaînée dynamique
     On importe le type 'edge_t'
---------------------------------------------------*/

#include "listedge.h"
#include "edge.h"

/* --------------------------------------------------
  2. Type table de hash 'hashtable_t'
-------------------------------------------------- */

typedef struct {
  int size;
  listedge_t* data;
} hashtable_t;

/* --------------------------------------------------
  3. Protoypes des fonctions realisant les opérations essentielles du type abstrait table de hash
-------------------------------------------------- */

/* Fonction de hashage */
unsigned int hash(char *s,int n) ;

/* crée et retourne une nouvelle table de m listes vides */
hashtable_t hashtable_new(int m)	;

/*
  Associe la valeur   v   a la clé   k   dans la table t.
  Si la clé   k   n'est pas encore dans la table, ajoute le couple [clé k , valeur v] à la table.
  Si la clé   k   est déjà présente dans la table, alors change la valeur associée à cette clé
  Retourne 1 si réussi, 0 sinon
*/
int hashtable_put(keys_t k, value_t v, hashtable_t t);

/* retourne 1 (true) si la clé k existe dans la table, 0 sinon */
int hashtable_contains_key(keys_t k, hashtable_t t);

/*
  Trouve et retourne la valeur associee à la cle k dans la table.
  Si la clé est présente, remplit la variable pointée par pv avec la valeur de la clé et retourne 1.
  Si la clé n'est pas présente, retourne 0.
*/
int hashtable_get_value(keys_t k, value_t* pv, hashtable_t t);


/* supprime la clé k et la valeur associée de la table t retourne 1 si la suppression est réalisée, 0 sinon */
int hashtable_delete_key(keys_t k, hashtable_t t);

/* supprime tous les éléments, détruit la table et retourne une table vide */
hashtable_t hashtable_delete(hashtable_t t);

/* Affiche toutes les paires [cle, valeur] contenues dans la table */
void hashtable_print(hashtable_t t);


#endif

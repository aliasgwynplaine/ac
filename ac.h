#ifndef AC_LIB_H
#define AC_LIB_H
/**
 * arbre cartesien
 * cartesian tree
 * 
 */
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "outils.h"

/* lol */
#define G 1
#define D 0
/* fin d'lol */
/**
 * this is the node struct
 * the pointers to the fils 
 * have to be the first members
 * since a pointer to a struct 
 * is a pointer to the first 
 * member of the struct. So, in 
 * this way, we can cast a ac_node_t**
 * as a ac_node_t * and access the 
 * pointed struct by calling the first
 * member of the struct. This is important
 * cuz node deletion relies in this 
 * behavior in order to delete a root
 * without adding additional variables
 * for that 'special' case.
 */
struct ac_node_t {
    struct ac_node_t * f[2];    /* 0 : droite, 1: gauche */
    char    k;                  /* clé */
    size_t  p;                  /* priorité */
};

/**
 * this is the tree _per se_
 * Remember ac_t->root is a 
 * ac_node_t. However, when you
 * cast &ac_t->root as a ac_node_t *
 * you can access the fils (only or UB) 
 * of the root node by simple indirection
 * but changing the value of the pntr
 * will also change the value of the 
 * ac_t->root variable
 */
struct ac_t {
    struct ac_node_t * root; /* racine */
    size_t  h;               /* hauteur */ 
    size_t sz;               /* size: nombre de noeuds */
};

struct ac_t * ac_init();
struct ac_node_t * ac_node_init();
void ac_node_rot(struct ac_node_t * n);
int ac_insert(struct ac_t * ac, char k, size_t p);
int ac_delete(struct ac_t * ac, char k);
struct ac_node_t * ac_search(struct ac_t * ac, char k);
void ac_node_destroy(struct ac_node_t * node);
void ac_destroy(struct ac_t * ac);

void ac_print(struct ac_node_t * n);
int  ac_check_pri(struct ac_node_t * acroot);
int  ac_empty(struct ac_t * ac);


#endif
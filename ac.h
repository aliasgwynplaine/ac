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

/* lol */
#define G 1
#define D 0
/* fin d'lol */

struct ac_node_t {
    char    k;                  /* clé */
    size_t  p;                  /* priorité */
    struct ac_node_t * f[2];    /* 0 : droite, 1: gauche */
};


struct ac_t {
    struct ac_node_t * root;   /* racine */
    size_t  h;          /* hauteur */ 
    size_t sz;          /* size: nombre de noeuds */
};

struct ac_t * ac_init();
void ac_insert(struct ac_t * ac, char k, size_t p);
struct ac_node_t * ac_search(struct ac_t * ac, char k);
void ac_node_destroy(struct ac_node_t * node);
void ac_destroy(struct ac_t * ac);

void ac_print(struct ac_t * ac);
int  ac_check_pri(struct ac_node_t * acroot);
int  ac_empty(struct ac_t * ac);


#endif
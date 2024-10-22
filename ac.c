#include "ac.h"


struct ac_t * ac_init() {
    struct ac_t * ac = malloc(sizeof * ac);
    ac->h    = 0;
    ac->sz   = 0;
    ac->root = NULL;

    return ac;
}

struct ac_node_t * ac_search(struct ac_t * ac, char k) {
    assert(ac->root != NULL);
    struct ac_node_t * n = ac->root;

    while (n != NULL) {
        if (k == n->k) return n;
        n = n->f[k < n->k];
    }

    return NULL;
}


void ac_node_destroy(struct ac_node_t * node) {
    if (node->f[1]) ac_node_destroy(node->f[1]);
    if (node->f[0]) ac_node_destroy(node->f[0]);
    free(node);
}


void ac_destroy(struct ac_t * ac) {
    assert(ac != NULL);
    ac_node_destroy(ac->root);
    free(ac);
}

void ac_print_(struct ac_node_t * n, struct q_t * q) {
/**
 * shamelessly plundered from 
 * https://hbfs.wordpress.com/2016/12/06/pretty-printing-a-tree-in-a-terminal/
 * :3
 */

    if (n) {
        printf("[%c:%ld]\n", n->k, n->p);
        
        for (int i = 0; i < q->h; i++) 
            if (q->b[i]) printf(" \u2502");
            else printf("   ");

        printf(" \u251c");
        q_push(q, true);
        ac_print_(n->f[0], q);
        q_pop(q);

        for (int i = 0; i < q->h; i++) 
            if (q->b[i]) printf(" \u2502");
            else printf("   ");

        printf(" \u2514");
        q_push(q, false);
        ac_print_(n->f[1], q);        
        q_pop(q);
    } else {
        printf("\u259e\n");
    }

}


void ac_print(struct ac_node_t * root) {
    struct q_t * q = q_init(64);
    ac_print_(root, q);
    q_destroy(q);
}


int ac_check_pri(struct ac_node_t * acroot) {
    struct ac_node_t * fd, * fg;
    fd = acroot->f[0];
    fg = acroot->f[1];

    if (fd) {
        if (fd->p < acroot->p) return false;
        else return ac_check_pri(fd);
    }

    if (fg) {
        if (fg->p < acroot->p) return false;
        else return ac_check_pri(fg);
    }

    return true;
}


int ac_empty(struct ac_t * ac) {
    assert(ac != NULL);

    return ac->root == NULL;
}
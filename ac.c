#include "ac.h"


struct ac_t * ac_init() {
    struct ac_t * ac = malloc(sizeof * ac);
    assert(ac != NULL);
    ac->h    = 0;
    ac->sz   = 0;
    ac->root = NULL;

    return ac;
}

struct ac_node_t * ac_node_init() {
    struct ac_node_t * n = malloc(sizeof * n);
    assert(n != NULL);
    n->f[0] = n->f[1] = NULL;

    return n;
}

void ac_node_rot(struct ac_node_t * n) {

}

/**
 * returns 
 *          1: meme k
 *          0: reussi
 */

int ac_insert(struct ac_t * ac, char k, size_t p) {
    assert(ac != NULL);
    //printf("insert %c %li\n", k, p);

    int h = 0; /* stack height */
    struct ac_node_t * s[1024]; /* stack. use thre->h */
    int                d[1024]; /* dirs to reconstrct the path */
    //s[0] = NULL;    
    struct ac_node_t * ptr = ac->root;
    
    while (ptr) {
        if (k == ptr->k) {
            /**
             * todo:
             * what happens if 
             * k == ptr->k but
             * p != ptr->p ??
             */
            return 1;
        }

        s[h] = ptr;
        d[h] = k < ptr->k;
        //printf("[%c:%ld]\n", ptr->k, ptr->p);
        //printf("d: %i\n", d[h]);
        ptr  = s[h]->f[d[h++]];
    }

    struct ac_node_t * n = ac_node_init();
    n->p = p;
    n->k = k;

    if (h > 0) {
        s[h-1]->f[d[h-1]] = n;
    } else // here ac is empty
        ac->root = n;

    ac->sz++;

    while (h > 0 && s[--h]->p > n->p) {
        if (h == 0) ac->root = n;
        else s[h-1]->f[d[h-1]] = n;
        
        if (d[h]) { /* n at left : rot right*/
            //printf("rotright\n");
            s[h]->f[1] = n->f[0];
            n->f[0]    = s[h];
        } else {   /* n at right : rot left */
            //printf("rotleft\n");
            s[h]->f[0] = n->f[1];
            n->f[1]    = s[h];
        }
    }
    
    return 0;
}


int ac_delete(struct ac_t * ac, char k) {
    assert(ac != NULL);
    //printf("delete %c\n", k);

    int h = 0; /* stack height */
    struct ac_node_t * p; /* parent */
    int                d; /* derniere dir pris*/

    struct ac_node_t * ptr = (struct ac_node_t *)&ac->root; // LOL! xd
    
    while (ptr && k != ptr->k) {
        d = k < ptr->k;
        //printf("[%c:%ld]\n", ptr->k, ptr->p);
        //printf("d: %i\n", d[h]);
        p   = ptr;
        ptr = ptr->f[d];
    }
    
    /*
    while (ptr->f[0] || ptr->f[1]) {
        int df;
        df = ptr->f[0] ? ptr->f[1] ? ptr->f[0] < ptr->f[1] : 0 : 1;
        p  = p->f[d] = ptr->f[1 - df];  // grand pere paradoxe
        ptr->f[1 - df] = ptr->f[1 - df]->f[df];
        p->f[df] = ptr;
        d = df;
    }
    */

    while ((ptr->f[0] || ptr->f[1])) {
        if (ptr->f[0]) {
            if (ptr->f[1]) {
                int df = ptr->f[0]->p < ptr->f[1]->p;
                printf("df: %d\n", df);
                p->f[d] = ptr->f[1 - df];
                p  =  ptr->f[1 - df];  // grand pere paradoxe
                ptr->f[1 - df] = ptr->f[1 - df]->f[df];
                p->f[df] = ptr;
                d = df;
            } else {
                p = p->f[d] = ptr->f[0]; // grand pere paradoxe
                ptr->f[0]   = ptr->f[0]->f[1];
                p->f[1]     = ptr;
                d = 0;
            }
        } else if (ptr->f[1]) {
            p = p->f[d] = ptr->f[0]; // grand pere paradoxe
            ptr->f[1]   = ptr->f[1]->f[0];
            p->f[0]     = ptr;
            d = 1;
        }
    }

    p->f[1 - d] = NULL; /* the meaning of d is inverted here */
    free(ptr);
    ac->sz--;
    
    return 0;
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
    assert(root != NULL);
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
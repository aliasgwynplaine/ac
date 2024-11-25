#include "test_ac.h"


struct ac_t * ac_init() {
    struct ac_t * ac = malloc(sizeof * ac);
    assert(ac != NULL);
    ac->root  = NULL;
    ac->h_max = 0;
    ac->h_moy = 0;
    ac->sz    = 0;

    return ac;
}

struct ac_node_t * ac_node_init() {
    struct ac_node_t * n = malloc(sizeof * n);
    assert(n != NULL);
    n->h    = 0;
    n->e    = 0;
    n->f[0] = n->f[1] = NULL;

    return n;
}


/**
 * inserts noeud with priorité aleatoire
 * note: you may want to set a seed before
 * call this fux for testing purposes
 */
int ac_alea_insert(struct ac_t * ac, size_t k) {
    double p = pseudo_unif();
    return ac_insert(ac, k, p);
}


/**
 * returns 
 *          1: meme k
 *          0: reussi
 */
int ac_insert(struct ac_t * ac, size_t k, double p) {
    assert(ac != NULL);
    //printf("insert %c %li\n", k, p);

    int h = 0; /* stack height | profondeur */
    int h_ = 0;
    struct ac_node_t * s[1024]; /* stack. use thre->h */
    int                d[1024]; /* dirs to reconstrct the path */
    //s[0] = NULL;    
    struct ac_node_t * lst = ac->root;
    struct ac_node_t * ptr = ac->root;
    
    while (ptr) {
        s[h] = ptr;
        d[h] = k < ptr->k;
        //printf("[%c:%ld]\n", ptr->k, ptr->p);
        //printf("d: %i\n", d[h]);
        if (ptr->e != 0) {
            lst = ptr;
            h_  = h;
        }
        ptr  = s[h]->f[d[h++]];
    }

    struct ac_node_t * n = ac_node_init();
    n->p = p;
    n->k = k;
    n->h = h;

    if (h > 0) {
        s[h-1]->f[d[h-1]] = n;
    } else // here ac is empty
        ac->root = n;

    ac->sz++;
    ac->h_max = ac->h_max < h ? h : ac->h_max;
    //ac->h_moy = ac->h_moy + (h - ac->h_moy) / ac->sz; // nice trick from sr

    while (h > 0 && s[--h]->p > n->p) {
        if (h == 0) ac->root = n;
        else s[h-1]->f[d[h-1]] = n;
        
        if (d[h]) { /* n at left : rot right*/
            //printf("rotright\n");
            s[h]->f[1] = n->f[0];
            n->f[0]    = s[h];
            n->e++;
            s[h]->e--;
            // todo: update profondeur of the right subtree
        } else {   /* n at right : rot left */
            //printf("rotleft\n");
            s[h]->f[0] = n->f[1];
            n->f[1]    = s[h];
            n->e++;
            s[h]->e--;
            // todo: update profondeur of the left subtree
        }

    }


    while (lst && lst != n) {
        if(d[h_] == 0) lst->e--;
        else lst->e++;

        lst = lst->f[d[h_++]];
    }
    
    return 0;
}



/**
 * returns
 *          0: sucess
 *          1: tree is empty
 */
int ac_delete(struct ac_t * ac, size_t k) {
    assert(ac != NULL);
    if (ac->sz == 0) return 1; /* tree is empty */
    //printf("delete %c\n", k);

    int h = 0; /* stack height */
    struct ac_node_t * p; /* grand-parent|grand-fils */
    int                d; /* derniere dir pris */
    int               df; /* nxt dir à prendre */

    struct ac_node_t * ptr = (struct ac_node_t *)&ac->root; // LOL! xd
    
    while (ptr && k != ptr->k) {
        d = k < ptr->k;
        //printf("[%c:%ld]\n", ptr->k, ptr->p);
        //printf("d: %i\n", d[h]);
        p   = ptr;
        ptr = ptr->f[d];
    }

    if (ptr->f[0] || ptr->f[1]) df = 0;

    while ((ptr->f[0] || ptr->f[1])) {
        if (ptr->f[0])
            if (ptr->f[1])
                df = ptr->f[1]->p < ptr->f[0]->p;
            else df = 0;
        else if (ptr->f[1]) df = 1;

        p = p->f[d]  = ptr->f[df]; // grand-pere paradox
        ptr->f[df]   = ptr->f[df]->f[1 - df];
        p->f[1 - df] = ptr;
        d = 1 - df;
        ptr->h++;
    }

    p->f[d] = NULL;
    free(ptr);
    ac->sz--;
    
    return 0;
}

/**
 * returns the first entry with key k
 * NULL if not found
 */
struct ac_node_t * ac_search(struct ac_t * ac, size_t k) {
    if (ac->sz == 0) return NULL;
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
        printf("[%ld:%0.2f|%ld|%i]\n", n->k, n->p, n->h, n->e);
        
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
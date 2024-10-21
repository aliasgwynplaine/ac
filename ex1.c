#include <stdio.h>
#include "ac.h"


struct ac_node_t * nodemaker(char k, size_t p) {
    struct ac_node_t * node = malloc(sizeof * node);
    assert(node != NULL);
    node->k = k;
    node->p = p;
    node->f[0] = node->f[1] = NULL;

    return node;
}


int main(int argc, char * argv[]){
    struct ac_t * ac;
    ac = ac_init();
    struct ac_node_t * node;
    node = nodemaker('H', 1);
    printf("node: %p\n", node);
    ac->root = node;
    node->f[0] = nodemaker('I', 10);
    node->f[0]->f[0] = nodemaker('J', 12);
    node->f[1] = nodemaker('D', 2);
    node = node->f[1];
    node->f[1] = nodemaker('B', 3);
    node->f[0] = nodemaker('E', 6);
    node->f[0]->f[0] = nodemaker('F', 7);
    node->f[0]->f[0]->f[0] = nodemaker('G', 9);
    node = node->f[1];
    node->f[0] = nodemaker('C', 8);
    node->f[1] = nodemaker('A', 5);
    
    printf("%d\n", ac_check_pri(ac->root));
    ac_destroy(ac);

    return 0;
}
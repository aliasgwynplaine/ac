#include <stdio.h>
#include "ac.h"

int main(int argc, char * argv[]){
    struct ac_t * ac;
    ac = ac_init();
    struct ac_node_t * node;
    ac_insert(ac, 'H', 1);
    ac_insert(ac, 'I', 10);
    ac_insert(ac, 'J', 12);
    ac_insert(ac, 'D', 2);
    ac_insert(ac, 'B', 3);
    ac_insert(ac, 'E', 6);
    ac_insert(ac, 'F', 7);
    ac_insert(ac, 'G', 9);
    ac_insert(ac, 'C', 8);
    ac_insert(ac, 'A', 5);

    printf("%d\n", ac_check_pri(ac->root));
    ac_print(ac->root);
    ac_destroy(ac);

    ac = ac_init();
    printf("------------------\n");
    ac_insert(ac, 'A', 5);
    ac_insert(ac, 'B', 3);
    ac_insert(ac, 'C', 8);
    ac_insert(ac, 'D', 2);
    ac_insert(ac, 'E', 6);
    ac_insert(ac, 'F', 7);
    ac_insert(ac, 'G', 9);
    ac_insert(ac, 'H', 1);
    ac_insert(ac, 'I', 10);
    ac_insert(ac, 'J', 12);
    printf("------------------\n");
    printf("%d\n", ac_check_pri(ac->root));
    ac_print(ac->root);
    ac_destroy(ac);

    ac = ac_init();
    ac_insert(ac, 'H', 1);
    ac_insert(ac, 'G', 9);
    ac_insert(ac, 'A', 5);
    ac_insert(ac, 'B', 3);
    ac_insert(ac, 'D', 2);
    ac_insert(ac, 'F', 7);
    ac_insert(ac, 'C', 8);
    ac_insert(ac, 'J', 12);
    ac_insert(ac, 'I', 10);
    ac_insert(ac, 'E', 6);
    printf("------------------\n");
    printf("%d\n", ac_check_pri(ac->root));
    ac_print(ac->root);
    ac_destroy(ac);

    ac = ac_init();
    ac_insert(ac, 'E', 6);
    ac_insert(ac, 'H', 1);
    ac_insert(ac, 'B', 3);
    ac_insert(ac, 'D', 2);
    ac_insert(ac, 'C', 8);
    ac_insert(ac, 'F', 7);
    ac_insert(ac, 'G', 9);
    ac_insert(ac, 'J', 12);
    ac_insert(ac, 'A', 5);
    ac_insert(ac, 'I', 10);
    printf("------------------\n");
    printf("%d\n", ac_check_pri(ac->root));
    ac_print(ac->root);
    ac_destroy(ac);


    return 0;
}
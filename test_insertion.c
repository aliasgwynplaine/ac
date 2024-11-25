#include <stdio.h>
#include <time.h>
#include <string.h>
#include "test_ac.h"

int main(int argc, char * argv[]){
    if (argc < 2) {
        fprintf(stderr, "usage %s: <nb_noeuds>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t nb = atol(argv[1]);
    FILE * fdvs = fopen("bench_depth_vs_size.data", "w");
    
    if (fdvs < 0) {
        perror("open");
        return errno;
    }

    FILE * fdeq = fopen("bench_equilibre.data", "w");
    
    if (fdeq < 0) {
        perror("open");
        return errno;
    }
    FILE * fdeqr = fopen("bench_equilibre_racine.data", "w");
    
    if (fdeq < 0) {
        perror("open");
        return errno;
    }


    struct ac_t * ac;
    ac = ac_init();


    for (int i = 0; i < nb; i++) {
        clock_t start = clock();

        ac_alea_insert(ac, i);

        clock_t fin = clock();
        double t = (double)(fin - start) / CLOCKS_PER_SEC;
        if (ac_check_pri(ac->root) == false) exit(EXIT_FAILURE);
        ac_update(ac);
        //ac_print(ac->root);
        fprintf(fdvs, "%ld %f\n", ac->sz, ac->d_moy);
        fprintf(fdeq, "%ld %f\n", ac->sz, ac->e_var);
        fprintf(fdeqr, "%ld %c\n", ac->sz, ac->root->e);
    }

    ac_destroy(ac);

    return 0;
}
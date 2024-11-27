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

    FILE * fitvdm = fopen("bench_insertion_time_vs_depth_moy.data", "w");
    
    if (fitvdm < 0) {
        perror("open");
        return errno;
    }

    FILE * fitvsz = fopen("bench_insertion_time_vs_size.data", "w");
    
    if (fitvsz < 0) {
        perror("open");
        return errno;
    }

    FILE * fstvdm = fopen("bench_search_time_vs_depth_moy.data", "w");
    
    if (fstvdm < 0) {
        perror("open");
        return errno;
    }

    FILE * fstvsz = fopen("bench_search_time_vs_size.data", "w");
    
    if (fstvsz < 0) {
        perror("open");
        return errno;
    }

    FILE * fdtvdm = fopen("bench_suppresion_time_vs_depth_moy.data", "w");
    
    if (fdtvdm < 0) {
        perror("open");
        return errno;
    }

    FILE * fdtvsz = fopen("bench_suppresion_time_vs_size.data", "w");
    
    if (fdtvsz < 0) {
        perror("open");
        return errno;
    }

    FILE * fdvsz = fopen("bench_depth_vs_size.data", "w");
    
    if (fdvsz < 0) {
        perror("open");
        return errno;
    }

    FILE * fhvsz = fopen("bench_hauteur_max_vs_size.data", "w");
    
    if (fhvsz < 0) {
        perror("open");
        return errno;
    }

    FILE * feq = fopen("bench_equilibre.data", "w");
    
    if (feq < 0) {
        perror("open");
        return errno;
    }

    FILE * feqr = fopen("bench_equilibre_racine.data", "w");
    
    if (feq < 0) {
        perror("open");
        return errno;
    }


    struct ac_t * ac;
    ac = ac_init();

    uint64_t * boite = malloc(nb * sizeof(*boite));

    for (int i = 0; i < nb; i++) {
        boite[i] = i;
    }

    shuffle(boite, nb);

    for (int i = 0; i < nb; i++) {
        clock_t start = clock();

        ac_alea_insert(ac, boite[i]);
        //ac_insert(ac, i, 1);

        clock_t fin = clock();
        double t = (double)(fin - start) / CLOCKS_PER_SEC;
        
        if (ac_check_pri(ac->root) == false) exit(EXIT_FAILURE);

        ac_update(ac);
        //ac_print(ac->root);
        fprintf(fitvdm, "%e %e\n", ac->d_moy, t);
        fprintf(fitvsz, "%ld %e\n", ac->sz, t);
        fprintf(fdvsz, "%ld %e\n", ac->sz, ac->d_moy);
        fprintf(fhvsz, "%ld %ld\n", ac->sz, ac->h_max);
        fprintf(feq, "%ld %f\n", ac->sz, ac->e_var);
        fprintf(feqr, "%ld %li\n", ac->sz, ac->root->e);
    }

    shuffle(boite, nb);

    for (int i = 0; i < nb; i++) {
        clock_t start = clock();

        ac_search(ac, boite[i]);

        clock_t fin = clock();
        double t = (double)(fin - start) / CLOCKS_PER_SEC;

        fprintf(fstvsz, "%ld %e\n", ac->sz, t);
        fprintf(fstvdm, "%f %e\n", ac->d_moy, t);

        start = clock();

        ac_delete(ac, boite[i]);

        fin = clock();
        t = (double)(fin - start) / CLOCKS_PER_SEC;
        ac_update(ac);

        fprintf(fdtvsz, "%ld %e\n", ac->sz, t);
        fprintf(fdtvdm, "%f %e\n", ac->d_moy, t);
    }

    shuffle(boite, nb);

    for (int i = 0; i < nb; i++) {
        clock_t start = clock();

        ac_delete(ac, boite[i]);

        clock_t fin = clock();
        double t = (double)(fin - start) / CLOCKS_PER_SEC;
        ac_update(ac);

        fprintf(fdtvsz, "%ld %e\n", ac->sz, t);
        fprintf(fdtvdm, "%f %e\n", ac->d_moy, t);
    }


    ac_destroy(ac);
    fclose(fitvdm);
    fclose(fitvsz);
    fclose(fdtvdm);
    fclose(fdtvsz);
    fclose(fstvdm);
    fclose(fstvsz);
    fclose(fhvsz);
    fclose(fdvsz);
    fclose(feq);
    fclose(feqr);
    free(boite);

    return 0;
}
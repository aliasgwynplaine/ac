#ifndef AC_OUTILS_H
#define AC_OUTILS_H

#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef uint64_t    u64;
typedef uint32_t    u32;
typedef u_char      uch;
typedef signed char sch;

struct q_t {
    int *  b; /* bits */
    size_t h; /* height */
};

struct q_t * q_init(size_t sz);
void q_destroy(struct q_t * q);
void q_push(struct q_t *q, int bit);
int  q_pop(struct q_t *q);

double pseudo_unif();
uint64_t pseudo_rand_u64();


#endif
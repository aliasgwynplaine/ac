#ifndef AC_OUTILS_H
#define AC_OUTILS_H

#include <stddef.h>
#include <stdlib.h>

struct q_t {
    int *  b; /* bits */
    size_t h; /* height */
};

struct q_t * q_init(size_t sz);
void q_destroy(struct q_t * q);
void q_push(struct q_t *q, int bit);
int  q_pop(struct q_t *q);


#endif
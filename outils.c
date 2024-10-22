#include "outils.h"

struct q_t * q_init(size_t sz) {
    struct q_t * q = malloc(sizeof *q);
    q->b = malloc(sz * sizeof (*q->b));
    q->h = 0;

    return q;
}

void q_destroy(struct q_t * q) {
    if (q->b) free(q->b);
    free(q);
} 

void q_push(struct q_t *q, int bit) {
    q->b[q->h++] = bit; // todo: what if it's full?
}

int q_pop(struct q_t *q) {
    if (q->h > 0)
        return q->b[--q->h];
    else return -1;
}

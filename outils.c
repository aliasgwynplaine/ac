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

double pseudo_unif() {
    int fd = open("/dev/urandom", O_RDONLY); 

    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    uint64_t r;

    if (read(fd, &r, sizeof(r)) != sizeof(r)) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return (double)r / (double)UINT64_MAX;
}

uint64_t pseudo_rand_u64() {
    int fd = open("/dev/urandom", O_RDONLY); 

    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    uint64_t r;

    if (read(fd, &r, sizeof(r)) != sizeof(r)) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return r;
}


void shuffle(uint64_t * a, uint64_t n) {
    uint64_t i;

    for (i = 0; i < n - 1; i++) {
        uint64_t j = i + pseudo_rand_u64() / (UINT64_MAX / (n - i) + 1);
        uint64_t t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}
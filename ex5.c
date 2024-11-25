#include <stdio.h>
#include "ac.h"

int main() {

    for (int i = 0; i < 10; i++) {
        printf("%f\n", pseudo_unif());
    }

    return 0;
}
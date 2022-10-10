#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <time.h>

#define NBMARKITER 10000000

int main() {
    double complex z1 = 1. + 3.*I;
    double z1sizeSq;
    size_t bi; clock_t t;

    t = clock();
    for (bi = 0; bi < NBMARKITER; bi++) {
        z1sizeSq = (double) (z1 * conj(z1));
    }
    t = clock() - t;
    
    printf("Size of z1 squared is %f, conj-method takes %zu ticks\n", z1sizeSq, t);

    t = clock();
    for (bi = 0; bi < NBMARKITER; bi++) {

        z1sizeSq = crealf(z1)*crealf(z1) + cimagf(z1)*cimagf(z1);
    }
    t = clock() - t;
    
    printf("Size of z1 squared is %f, direct method takes %zu ticks\n", z1sizeSq, t);

    return 0;
}
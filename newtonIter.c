#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <complex.h>

#define X0 -10.
#define ZEROCHARVAL 48
#define TOL 1e-3

double getZero(char degree, char zeroIndex) {
    switch (degree) {
    case '1':
        return 1.;
    case '2':
        switch (zeroIndex) {
            case '0':
                return 1.;
            case '1':
                return -1.;
            
            default:
            fprintf(stderr, "unexpected zeroIndex\n");
            exit(1);
        }


    default:
        fprintf(stderr, "unexpected degree\n");
        exit(1);
    }

}

int main() {
    char degree = '2';
    char zeroIndex = '0';
    double x = X0;
    size_t nIter = 0;
    
    switch (degree) {
    case '1':
        x = 1.;
        nIter = 1;
        break;
    case '2':
        for (;;) {
            if (fabs(x - 1.) < TOL) {
                break;
            }
            if (fabs(x + 1.) < TOL) {
                zeroIndex = '1';
                break;
            }
            x = (x + 1./x)/2.;
            printf("%zu\n",++nIter);
        }
        break;
    // insert further cases

    default:
        fprintf(stderr, "unexpected degree\n");
        exit(1);
    }

    printf("Wow vi hittar nollställe nr %c till x^%d - 1 på %zu iteration(er) när vi startgissar på %f (vårt värde är %f och det borde vara %d)\n", zeroIndex, degree - ZEROCHARVAL, nIter, X0, x, getZero(degree, zeroIndex));
    
    return 0;
}
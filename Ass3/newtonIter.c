#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define X0 1.
#define Y0 4.
#define ZEROCHARVAL 48
#define TOLSQ 1e-6
#define ABSSQ(zfl) (crealf(zfl)*crealf(zfl) + cimagf(zfl)*cimagf(zfl))

/* double getZero(char degree, char zeroIndex) {
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

} */

int main() {
    char degree = '9';
    char zeroIndex;
    float realdum, imagdum;
    complex float zDum;
    // Initial guess, initialize iteration counter
    complex float zVal = X0 + Y0*I;
    size_t nIter = 0;
    
    // Commence spaghetti
    switch (degree) {
    case '1':
        zeroIndex = '0';
        zVal = (complex float) 1.;
        nIter = 1;
        break;
    case '2':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal + 1.) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            zVal = (zVal + 1./zVal)/2.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '3':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal + (0.5 - 0.8660254037844386*I)) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal + (0.5 + 0.8660254037844386*I)) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            zVal = (2.*zVal + 1./(zVal*zVal))/3.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '4':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal - I) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal + 1.) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            if (ABSSQ(zVal + I) < TOLSQ) {
                zeroIndex = '3';
                break;
            }
            zVal = (3.*zVal + 1./(zVal*zVal*zVal))/4.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '5':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal - (0.309016994374948 + 0.951056516295153*I)) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal + 0.809016994374947 - 0.587785252292473*I) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            if (ABSSQ(zVal + 0.809016994374947 + 0.587785252292473*I) < TOLSQ) {
                zeroIndex = '3';
                break;
            }
            if (ABSSQ(zVal - 0.309016994374948 + 0.951056516295153*I) < TOLSQ) {
                zeroIndex = '4';
                break;
            }
            zDum = zVal*zVal;
            zVal = (4.*zVal + 1./(zDum*zDum))/5.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '6':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal - (0.5 + 0.8660254037844386*I)) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal + 0.5 - 0.8660254037844386*I) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            if (ABSSQ(zVal + 1.) < TOLSQ) {
                zeroIndex = '3';
                break;
            }
            if (ABSSQ(zVal + 0.5 + 0.8660254037844386*I) < TOLSQ) {
                zeroIndex = '4';
                break;
            }
            if (ABSSQ(zVal - 0.5 + 0.8660254037844386*I) < TOLSQ) {
                zeroIndex = '5';
                break;
            }
            zDum = zVal*zVal;
            zVal = (5.*zVal + 1./(zDum*zDum*zVal))/6.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '7':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal - (0.623489801858734 + 0.781831482468030*I)) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal + 0.222520933956314 - 0.974927912181824*I) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            if (ABSSQ(zVal + 0.900968867902419 - 0.433883739117558*I) < TOLSQ) {
                zeroIndex = '3';
                break;
            }
            if (ABSSQ(zVal + 0.900968867902419 + 0.433883739117558*I) < TOLSQ) {
                zeroIndex = '4';
                break;
            }
            if (ABSSQ(zVal + 0.222520933956314 + 0.974927912181824*I) < TOLSQ) {
                zeroIndex = '5';
                break;
            }
            if (ABSSQ(zVal - 0.623489801858734 + 0.781831482468030*I) < TOLSQ) {
                zeroIndex = '6';
                break;
            }
            zDum = zVal*zVal;
            zVal = (6.*zVal + 1./(zDum*zDum*zDum))/7.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '8':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal - (0.707106781186548 + 0.707106781186547*I)) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal - I) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            if (ABSSQ(zVal + 0.707106781186548 - 0.707106781186547*I) < TOLSQ) {
                zeroIndex = '3';
                break;
            }
            if (ABSSQ(zVal + 1.) < TOLSQ) {
                zeroIndex = '4';
                break;
            }
            if (ABSSQ(zVal + 0.707106781186548 + 0.707106781186547*I) < TOLSQ) {
                zeroIndex = '5';
                break;
            }
            if (ABSSQ(zVal + I) < TOLSQ) {
                zeroIndex = '6';
                break;
            }
            if (ABSSQ(zVal - 0.707106781186548 + 0.707106781186547*I) < TOLSQ) {
                zeroIndex = '7';
                break;
            }
            zDum = zVal*zVal;
            zVal = (7.*zVal + 1./(zDum*zDum*zDum*zVal))/8.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    case '9':
        for (;;) {
            realdum = fabsf(crealf(zVal));
            imagdum = fabsf(cimagf(zVal));
            if ((realdum > 1e10) || (imagdum > 1e10)) {
                zeroIndex = 'F';
                break;
            }
            if ((realdum*realdum + imagdum*imagdum < TOLSQ)) {
                zeroIndex = 'F';
                break;
            }
            if (ABSSQ(zVal - 1.) < TOLSQ) {
                zeroIndex = '0';
                break;
            }
            if (ABSSQ(zVal - (0.766044443118978 + 0.642787609686539*I)) < TOLSQ) {
                zeroIndex = '1';
                break;
            }
            if (ABSSQ(zVal - (0.173648177666930 + 0.984807753012208*I)) < TOLSQ) {
                zeroIndex = '2';
                break;
            }
            if (ABSSQ(zVal + 0.500000000000000 - 0.866025403784439*I) < TOLSQ) {
                zeroIndex = '3';
                break;
            }
            if (ABSSQ(zVal + 0.939692620785908 - 0.342020143325669*I) < TOLSQ) {
                zeroIndex = '4';
                break;
            }
            if (ABSSQ(zVal + 0.939692620785908 + 0.342020143325669*I) < TOLSQ) {
                zeroIndex = '5';
                break;
            }
            if (ABSSQ(zVal + 0.500000000000000 + 0.866025403784439*I) < TOLSQ) {
                zeroIndex = '6';
                break;
            }
            if (ABSSQ(zVal - 0.173648177666930 + 0.984807753012208*I) < TOLSQ) {
                zeroIndex = '7';
                break;
            }
            if (ABSSQ(zVal - 0.766044443118978 + 0.642787609686539*I) < TOLSQ) {
                zeroIndex = '8';
                break;
            }
            zDum = zVal*zVal;
            zDum *= zDum;
            zVal = (8.*zVal + 1./(zDum*zDum))/9.;
            nIter++;

            printf("%zu\n",nIter);
            printf("%f + %fi\n",crealf(zVal),cimagf(zVal));
        }
        break;
    // No further cases. Hyyyyyype.

    default:
        fprintf(stderr, "unexpected degree\n");
        exit(1);
    }

    printf("Wow vi hittar nollställe nr %c till x^%d - 1 på %zu iteration(er) när vi startgissar på %f + %fi\n", zeroIndex, degree - ZEROCHARVAL, nIter, X0, Y0);
    printf("(vårt värde är %f + %fi)\n", crealf(zVal), cimagf(zVal));
    return 0;
}
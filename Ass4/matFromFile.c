#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("init","r");
    if (file == NULL) {
        perror("error:");
        exit(1);
    }

    fseek(file,0,SEEK_END);
    const size_t filesize = ftell(file)/sizeof(char);
    fseek(file,0,SEEK_SET);

    char* fileStr = (char*) malloc(filesize*sizeof(char));
    fread(fileStr, sizeof(char), filesize, file);

    fclose(file);

    //printf ("Splitting string \"%s\" into tokens:\n",fileStr);
    char* tok; const char whitespace[3] = " \n";
    unsigned long nRows = strtoul(strtok(fileStr, whitespace),NULL,10);
    unsigned long nCols = strtoul(strtok(NULL, whitespace),NULL,10);
    printf("Vi har %zu rader och %zu kolumner\n", nRows, nCols);

    // Mallocation & initialisation of our h1 matrix
    float* h1 = malloc((nRows+2)*(nCols+2)*sizeof(float));
    unsigned long ix;
    for (ix = 0; ix < (nRows+2)*(nCols+2); ix++) {
        h1[ix] = 0.f;
    }

    // Misstänker att det finns nåt mindre ass sätt att göra detta på, men detta får duga tillsvidare.
    // Dumping of file init into matrix h1 (with zero padding).
    unsigned long jx;
    while ((tok = strtok(NULL, whitespace)) != NULL) {
        ix = strtoul(tok, NULL, 10);
        jx = strtoul(strtok(NULL, whitespace), NULL, 10);
        h1[(ix+1)*(nCols+2) + (jx+1)] = strtof(strtok(NULL, whitespace), NULL);
        printf("Hello, (%zu,%zu) : %f\n", ix, jx, h1[(ix+1)*(nCols+2) + (jx+1)]);
    }

    //printf("Element (1,3) är nu %f\n", h1[2*(nCols+2)+4]);

    free(fileStr);
    free(h1);

    return 0;
}
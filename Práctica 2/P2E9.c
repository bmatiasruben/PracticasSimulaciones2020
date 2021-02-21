#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void *malloc(size_t size);

int readNumber(char archivo[], double *num) {
    static FILE *file;
    if (!file) {
        file = fopen(archivo, "rt");
    }
    if (fscanf(file, "%lf", num) == EOF) {
        return 0;
        fclose(file);
    } else {
        return 1;
    }
}

int readFile(char archivo[], double **numbers, int *size) {
    FILE *file = fopen(archivo,"rt");
    double numberRead;
    int sizeAux = 0;
    *numbers = (double*)malloc(sizeof(double));

    while (readNumber(archivo, &numberRead)) {
        (*numbers)[sizeAux] = numberRead;
        sizeAux++;
        *numbers = (double*)realloc(*numbers, (sizeAux + 1) * sizeof(double));
    }

    *size = sizeAux;
    fclose(file);
}

int main() {
    int size;
    double *numbers;

    readFile("allocRealNumbersRead.txt",&numbers,&size);

    for (int i = 0; i < size; i++) {
        printf("%d    %f\n", i+1, numbers[i]);
    }
    free(numbers);
}



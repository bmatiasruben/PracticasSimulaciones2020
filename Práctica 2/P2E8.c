#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void *malloc(size_t size);

int readFile(char archivo[],double **numbers,int *size) {
    FILE *file = fopen(archivo,"rt");
    fscanf(file,"%d",size);
    
    *numbers = (double*)malloc(*size * sizeof(double));
    for (int i = 0; i < *size; i++) {
        fscanf(file,"%lf",(*numbers) + i);
    }
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



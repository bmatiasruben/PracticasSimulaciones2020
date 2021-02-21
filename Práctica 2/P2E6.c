#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int lee_nro(char archivo[], double *num) {
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

int main() {
    double a;

    while(lee_nro("realNumbersRead.txt", &a)) {
        printf("%g\n", a);
    }
}

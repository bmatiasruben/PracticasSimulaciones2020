#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE *fp;

    fp = fopen("Matriz_Ej4a.txt", "w+");

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                for(int l = 0; l < 4; l++) {
                    for(int m = 0; m < 4; m++) {
                        for(int n = 0; n < 4; n++) {
                            fprintf(fp, "%d %d %d %d %d %d\n", i, j, k, l, m, n);
                        }
                    }
                }
            }
        }
    }

    fclose(fp);
}
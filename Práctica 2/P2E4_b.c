#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double trperim(double r1[], double r2[], double r3[]);
double tarea(double r1[], double r2[], double r3[]);

int main() {
    FILE *fp2;
    FILE *fp;
    int vector[6][4096] = {0};
    double perim[4096] = {0};
    double area[4096] = {0};
    double r1[2] = {0};
    double r2[2] = {0};
    double r3[2] = {0};

    fp2 = fopen("Matriz_Ej4a.txt", "r+");
    fp = fopen("Resultados_Ej4b.txt", "w+");

    for (int j = 0; j < 4096; j++) {
        fscanf(fp2, " %d %d %d %d %d %d\n", &vector[0][j], &vector[1][j], &vector[2][j], &vector[3][j], &vector[4][j], &vector[5][j]);
        r1[0] = (double) vector[0][j];
        r1[1] = (double) vector[1][j];
        r2[0] = (double) vector[2][j];
        r2[1] = (double) vector[3][j];
        r3[0] = (double) vector[4][j];
        r3[1] = (double) vector[5][j];
        // printf("%lf %lf %lf %lf %lf %lf\n", r1[0], r1[1], r2[0], r2[1], r3[0], r3[1]);
        perim[j] = trperim(r1, r2, r3);
        // printf("%f \n", perim[j]);
        area[j] = tarea(r1, r2, r3);
        fprintf(fp,"%d %f %f \n", j+1, perim[j], area[j]);
    }
    fclose(fp2);
}

double trperim(double r1[], double r2[], double r3[]) {
    double d1;
    double d2;
    double d3;
    double perim;

    d1 = sqrt(pow((r2[0]-r1[0]),2)+pow((r2[1]-r1[1]),2));
    d2 = sqrt(pow((r2[0]-r3[0]),2)+pow((r2[1]-r3[1]),2));
    d3 = sqrt(pow((r3[0]-r1[0]),2)+pow((r3[1]-r1[1]),2));
    perim = d1 + d2 + d3;
    return perim;
}

double tarea(double r1[], double r2[], double r3[]) {
    double d1;
    double d2;
    double d3;
    double s;
    double area;

    d1 = sqrt(pow((r2[0]-r1[0]),2)+pow((r2[1]-r1[1]),2));
    d2 = sqrt(pow((r2[0]-r3[0]),2)+pow((r2[1]-r3[1]),2));
    d3 = sqrt(pow((r3[0]-r1[0]),2)+pow((r3[1]-r1[1]),2));
    s = (d1 + d2 + d3) / 2;

    area = sqrt(s * (s - d1) * (s - d2) * (s - d3));
    return area;
}
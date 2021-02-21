#include <stdio.h>
#include <math.h>

double tarea(double r1[], double r2[], double r3[]);

int main() {
    double r1[2];
    double r2[2];
    double r3[2];
    double area;

    printf("Ingrese la posicion x del vertice 1: ");
    scanf("%lf", &r1[0]);
    printf("Ingrese la posicion y del vertice 1: ");
    scanf("%lf", &r1[1]);

    printf("Ingrese la posicion x del vertice 2: ");
    scanf("%lf", &r2[0]);
    printf("Ingrese la posicion y del vertice 2: ");
    scanf("%lf", &r2[1]);

    printf("Ingrese la posicion x del vertice 3: ");
    scanf("%lf", &r3[0]);
    printf("Ingrese la posicion y del vertice 3: ");
    scanf("%lf", &r3[1]);

    area = tarea(r1, r2, r3);
    printf("El area del triangulo es: %lf", area);
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


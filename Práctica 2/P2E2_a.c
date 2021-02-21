#include <stdio.h>
#include <math.h>

double trperim(double r1[], double r2[], double r3[]);

int main() {
    double r1[2];
    double r2[2];
    double r3[2];
    double per;

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

    per = trperim(r1, r2, r3);
    printf("El perimetro del triangulo es: %lf", per);
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


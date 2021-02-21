#include <stdio.h>

int main() {
    float t;
    float t0 = 5;
    float accel = 2;
    float pos;

    printf("Calculo de posicion partiendo del reposo con a = 2 m/s^2\n");
    printf("Ingrese el tiempo en segundos para calcular la posicion: ");
    escaneo: scanf("%f", &t);

    if (t < 0) {
        printf("ERROR: Ingrese un tiempo positivo en segundos\n");
        goto escaneo;
    } else if (t < t0) {
        pos = accel * t * t / 2;
    } else {
        pos = accel * t0 * t0 / 2 + accel * t0 * (t - t0);
    }

    printf("La posicion a %f", t);
    printf(" segundos es: %f", pos);
    printf(" m");
}
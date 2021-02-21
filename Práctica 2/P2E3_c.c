#include <stdio.h>
#include <math.h>
#include <stdbool.h>

float meanf(float beta, float min);

int main() {
    float beta = 0;
    float temp = 0;
    float min = 0;
    float sol;
    bool solved = false;

    ingreso: printf("Ingrese la temperatura del sistema en K: ");
    scanf("%f", &temp);

    if (temp < 0) {
        printf("Ahora una temperatura real, tipo positiva y distinta de cero.\n");
        goto ingreso;
    } else if (temp == 0) {
        printf("Ahora una temperatura real, tipo positiva y distinta de cero.\n");
        goto ingreso;
    } else {
        beta = 1. / temp;
    }

    printf("Ingrese el valor inicial de m (mayor que cero): ");
    scanf("%f", &min);

    if (min <= 0) {
        printf("Mayor que cero dije.\n");
    } else {
        sol = meanf(beta, min);
        if (sol == -2) {
            printf("Superado el numero maximo de pasos, modificar el valor incial de m. Proba con algo mas chico.\n");
            goto ingreso;
        } else {
            printf("La solucion es m = %f", sol);
        }
    }    
}

float meanf(float beta, float min) {
    bool solved = false;
    float m;
    float m1;
    int cuentas = 0;

    m = min;

    while (solved == false) {
        m = atanh(m) / beta;
        cuentas += 1;
        if (cuentas == pow(10,10)) {
            m = -2;
            solved = true;
        } else {
            if ( m - atanh(m) / beta < 0.001) {
                solved = true;
            }
        }
    }
    return m;
}
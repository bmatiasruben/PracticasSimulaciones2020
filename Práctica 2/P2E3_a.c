#include <stdio.h>
#include <math.h>

int esprimo(int n);

int main() {
    int entero;
    int resultado;

    ingreso: printf("Ingrese un entero: ");
    scanf("%d", &entero);

    // int medio = entero % 2;
    // printf("%d", medio);

    if (entero <= 0) {
        printf("Dije un entero.\n");
        goto ingreso;
    } else if (entero == 1) {
        printf("Es y no es, usted me entiende. Ingresa otro entero.\n");
        goto ingreso;
    } else if (entero == 2) {
        resultado = 1;
    } else {
        resultado = esprimo(entero);
    }
    
    if (resultado == 0) {
        printf("%d", entero);
        printf(" no es primo.");
    } else {
        printf("%d", entero);
        printf(" es primo.");
    }
}

int esprimo(int n) {
    int resto;
    int falso = 0;
    int verd = 1;
    int total = 0;
    for (int i = 2; i < n; i++) {
        resto = n % i;
        if (resto == 0) {
            total += 1;
        }
    }
    if (total == 0) {
        return verd;
    } else {
        return falso;
    }
}
#include <stdio.h>
#include <math.h>

int esprimo(int n);

int main() {
    int total = 0;
    int n = 2;
    int resultado;

    while (total < 100) {
        resultado = esprimo(n);
        if (resultado == 1) {
            total += 1;
            printf("%d", n);
            printf("\n");
        }
        n += 1;
    }
}

int esprimo(int n) {
    int resto;
    int falso = 0;
    int verd = 1;
    int total = 0;

    if (n == 2) {
        return verd;
    } else {
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
}
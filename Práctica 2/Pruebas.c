#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    const float a = 5;
    int *p;
    int r = 3521;

    p = &r;

    printf("%d", p);
}
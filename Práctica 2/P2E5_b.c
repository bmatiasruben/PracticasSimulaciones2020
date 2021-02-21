#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h> 

void InvertirString(char *string);
int string_length(char*);

int main() {
    char string[200];

    printf("Escriba un string\n");
    gets(string);
    // printf("%d\n", string_length(string));
    InvertirString(string);
    // printf("%d\n", string_length(string));
    printf("El string invertido es: \"%s\".\n", string);
}

void InvertirString(char *string) {
    int largo;
    char *begin, *end, temp;

    largo = string_length(string);

    begin = string;
    end = string;

    for (int i = 0; i < (largo - 1); i++) {
        end++;
    }

    for (int k = 0; k < largo / 2; k++) {
        temp = *end;
        *end = *begin;
        *begin = temp;

        begin++;
        end--;
    }
}

int string_length(char *pointer) {
    int c = 0;

    while( *(pointer+c) != '\0' )
        c++;
    return c;
}
 
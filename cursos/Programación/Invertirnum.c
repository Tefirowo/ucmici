#include <stdio.h>
#include <string.h>

void invertirCadena(char str[]);

int main() {
    char secuencia[100];

    printf("Ingresa la secuencia de numeros: ");
    scanf("%99s", secuencia);

    printf("Original: %s\n", secuencia);
    invertirCadena(secuencia);

    printf("Secuencia invertida: %s\n", secuencia);

    return 0;
}

void invertirCadena(char str[]) {
    int inicio = 0;
    int fin = strlen(str) - 1;

    while (inicio < fin) {
        char temp = str[inicio];
        str[inicio] = str[fin];
        str[fin] = temp;
        inicio++;
        fin--;
    }
}
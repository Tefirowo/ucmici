#include <stdio.h>

int main() {
    int iteraciones;
    double pi = 3.0;
    double signo = 1.0;
    printf("Introduce el numero de iteraciones: ");
    scanf("%d", &iteraciones);
    for (int i = 1; i <= iteraciones; i++) {
        double n = 2.0 * i;
        double termino = 4.0 / (n * (n + 1.0) * (n + 2.0));
        pi += signo * termino;
        signo *= -1.0;
    }
    printf("\nEl valor aproximado de Pi con %d iteraciones es: %.100f\n", iteraciones, pi);

    return 0;
}
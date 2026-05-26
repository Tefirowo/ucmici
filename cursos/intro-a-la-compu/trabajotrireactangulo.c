#include <stdio.h> /* Biblioteca para entrada y salida [11] */

int main() {

    int base, altura, area, perimetro;
    printf("Ingrese el valor de la base (entero): ");
    scanf("%d", &base);
    printf("Ingrese el valor de la altura (entero): ");
    scanf("%d", &altura);

    /*Aqui el arreglo*/

    area = base * altura;
    perimetro = 2 * (base + altura);

    printf("\n--- Resultados ---\n");
    printf("El area del rectangulo es: %d\n", area);
    printf("El perimetro del rectangulo es: %d\n", perimetro);
    return 0;
}
#include <stdio.h>
int main()
{
    int numero;
    int suma = 0;
    int cantidad = 0;
    int maximo = 0;
    printf("=== Calculadora de números positivos ===\n");
    printf("Ingresa números enteros positivos.\n");
    printf("Ingresa 0 o un numero negativo para terminar.\n\n");
    
    printf("Ingresa un numero: ");
    scanf("%d", &numero);

    if (numero <= 0)
    {
        printf("Numero menor o igual a 0: chao pescao! \n");
        return 0;
    }
    else
    {

    }


    if (cantidad > 0)
    {
        printf("\n --- Resultados del programa --- \n");
        printf("Cantidad de números ingresados: %d\n", cantidad);
        printf("Suma total: %d\n", suma);
        printf("Número más grande: %d\n", maximo);
        /* continúe aquí con los datos siguientes */
    }
    else
    {
        printf("\nNo se ingresaron números positivos.\n");
    }
    return 0;
}
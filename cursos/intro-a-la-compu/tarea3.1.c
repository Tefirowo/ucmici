#include <stdio.h>

int main()
{
    int numero;
    int suma = 0;
    int cantidad = 0;
    int maximo = 0;
    int minimo = 0;
    double promedio = 0;

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
        maximo = numero;
        minimo = numero;

        while (numero > 0)
        {
            cantidad++;
            suma += numero;

            if (numero > maximo)
            {
                maximo = numero;
            }
            
            if (numero < minimo)
            {
                minimo = numero;
            }


            printf("Ingresa un numero: ");
            scanf("%d", &numero);
        }
    }

    if (cantidad > 0)
    {
        promedio = (double)suma / cantidad;
        printf("\nNumero menor o igual a 0: se presentarán los \n");
        printf("--- Resultados del programa --- \n");
        printf("Cantidad de números ingresados: %d\n", cantidad);
        printf("Suma total: %d\n", suma);
        printf("Promedio: %f\n", promedio);
        printf("Número más grande: %d\n", maximo);
        printf("Número menor: %d\n", minimo);
        printf("Chao pescao!\n");
    }
    else
    {
        printf("\nNo se ingresaron números positivos.\n");
    }

    return 0;
}
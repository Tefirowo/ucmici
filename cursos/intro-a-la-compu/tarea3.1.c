#include <stdio.h>

int main()
{
    int numero;
    int suma = 0;
    int cantidad = 0;
    int maximo = 0;
    int minimo = 0; // Agregamos la variable para el menor

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
        // Como el primer número ya es positivo, lo asignamos como base
        maximo = numero;
        minimo = numero;

        while (numero > 0)
        {
            cantidad++;
            suma += numero;

            // Comparación para el máximo
            if (numero > maximo)
            {
                maximo = numero;
            }
            
            // Comparación para el mínimo
            if (numero < minimo)
            {
                minimo = numero;
            }

            // Pedimos el siguiente número antes de terminar el ciclo
            printf("Ingresa un numero: ");
            scanf("%d", &numero);
        }
    }

    if (cantidad > 0)
    {
        printf("\n --- Resultados del programa --- \n");
        printf("Cantidad de números ingresados: %d\n", cantidad);
        printf("Suma total: %d\n", suma);
        // Hacemos el cast a float para que el promedio dé con decimales
        printf("Promedio: %.2f\n", (float)suma / cantidad);
        printf("Número más grande: %d\n", maximo);
        printf("Número menor: %d\n", minimo);
    }
    else
    {
        printf("\nNo se ingresaron números positivos.\n");
    }

    return 0;
}
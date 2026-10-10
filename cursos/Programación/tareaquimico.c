#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main () {

    char nombres [100][50]; 
    int size; 

    printf("Cuantos nombres quimicos desea ingresar? (Max 100): ");
    scanf("%d", &size);
    getchar(); 

    // 1. Lectura de las fórmulas
    for (int i = 0; i < size; i++) {
        printf("Ingrese la f\242rmula %d: ", i + 1);
        fgets(nombres[i], 50, stdin);
        
        nombres[i][strcspn(nombres[i], "\n")] = '\0';
    }

    // 2. Cada fórmula
    printf("\n--= RESULTADOS =--\n");
    for (int i = 0; i < size; i++) {
        
        // Validar si la fórmula empieza con número (inválida)
        if (isdigit(nombres[i][0])) {
            printf("\nFórmula %s: Inválida (no puede comenzar con un número).\n", nombres[i]);
            continue;
        }

        // Arreglos 
        char simbolos[20][3];
        int cantidades[20];
        int total_elementos = 0;

        int j = 0;
        int invalida = 0;

        while (nombres[i][j] != '\0') {
            if (isupper(nombres[i][j])) {
                char elem[3] = {0};
                elem[0] = nombres[i][j];
                j++;

                if (islower(nombres[i][j])) {
                    elem[1] = nombres[i][j];
                    j++;
                }

                int cant = 0;
                while (isdigit(nombres[i][j])) {
                    cant = cant * 10 + (nombres[i][j] - '0');
                    j++;
                }
                if (cant == 0) cant = 1; 

                int existe = 0;
                for (int k = 0; k < total_elementos; k++) {
                    if (strcmp(simbolos[k], elem) == 0) {
                        cantidades[k] += cant;
                        existe = 1;
                        break;
                    }
                }
                if (!existe) {
                    strcpy(simbolos[total_elementos], elem);
                    cantidades[total_elementos] = cant;
                    total_elementos++;
                }
            } else {
                invalida = 1;
                break;
            }
        }

        // Imprir final
        if (invalida || total_elementos == 0) {
            printf("\nFórmula %s: Inválida.\n", nombres[i]);
        } else {
            printf("\nEn la f\242rmula %s tienes: ", nombres[i]);
            for (int k = 0; k < total_elementos; k++) {
                printf("%d de %s", cantidades[k], simbolos[k]);

                if (k < total_elementos - 2) {
                    printf(", ");
                } else if (k == total_elementos - 2) {
                    printf(" y ");
                }
            }
            printf(".\n");
        }
    }

    return 0;
}
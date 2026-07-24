#include <stdio.h>
#include <string.h>

void agregarNombres(FILE *archivo);
void mostrarNombres(void);

int main(void) {
    char opcion;
    FILE *archivo;

    archivo = fopen("nombre.dat", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do {
        agregarNombres(archivo);
        printf("2.- Continua ingresando [s/n]: ");
        scanf(" %c", &opcion);
        printf("\n");
    } while (opcion == 's' || opcion == 'S');

    fclose(archivo);
    mostrarNombres();
    return 0;
}

void agregarNombres(FILE *archivo) {
    char nombre[31];

    printf("1.- Ingrese su nombre: ");
    scanf(" %30s", nombre);
    fprintf(archivo, "%s\n", nombre);
}

void mostrarNombres(void) {
    FILE *archivo;
    char nombre[31];
    int contador;

    contador = 1;
    archivo = fopen("nombre.dat", "r");
    if (archivo == NULL) {
        printf("Error al leer el archivo.\n");
        return;
    }

    while (fgets(nombre, sizeof(nombre), archivo) != NULL) {
        nombre[strcspn(nombre, "\n")] = '\0';
        printf("%d.- %s\n", contador, nombre);
        contador++;
    }

    fclose(archivo);
}
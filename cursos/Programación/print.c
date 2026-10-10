#include <stdio.h>

int main(){

    FILE *t;
    int edad, añonacimiento;
    char nombre[30];
    printf("Hola amigo, dame unos datos plis...\n");
    printf("Primero, cuál es tu edad?: ");
    scanf("%d", &edad);
    printf("Segundo, cuál es tu nombre?: ");
    scanf("%s", nombre);
    

    t = fopen("data.txt", "a");
    fprintf(t, "-= Datos usuario =-\nEdad: %d\nNombre: %s\nAño nacimiento: %d\n", edad, nombre, 2026-edad);
    fclose(t);
    return 0;
}
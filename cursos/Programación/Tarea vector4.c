#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define TAM 5

// Teclas
#define ESC 27
#define ENTER 13
#define FLECHA_ARRIBA 72
#define FLECHA_ABAJO 80
#define FLECHA_IZQUIERDA 75
#define FLECHA_DERECHA 77

// Prototipos
void limpiarPantalla();
void pausa();
void imprimirMatriz(int matriz[TAM][TAM], char *nombre);
int sumarElementos(int matriz[TAM][TAM]);
double promedioMatriz(int matriz[TAM][TAM]);
int buscarMayor(int matriz[TAM][TAM]);
int buscarMenor(int matriz[TAM][TAM]);
int contarPares(int matriz[TAM][TAM]);
void ingresarDatosInteractivo(int matriz[TAM][TAM], char *nombre);
int menuNavegable(const char *opciones[], int numOpciones);

int main() {
    int maquinaA[TAM][TAM] = {0};
    int maquinaB[TAM][TAM] = {0};
    int datosIngresados = 0;

    const char *opcionesMenu[] = {
        "1. Ingresar datos de forma interactiva (A y B)",
        "2. Mostrar ambas matrices",
        "3. Comparar suma total de elementos",
        "4. Mostrar promedios",
        "5. Mostrar maximos y minimos",
        "6. Contar numeros pares en cada maquina",
        "7. Salir"
    };
    int totalOpciones = 7;
    int seleccion;

    do {
        seleccion = menuNavegable(opcionesMenu, totalOpciones);

        switch(seleccion) {
            case 0: // Ingresar datos
                ingresarDatosInteractivo(maquinaA, "Maquina A");
                ingresarDatosInteractivo(maquinaB, "Maquina B");
                datosIngresados = 1;
                printf("\n¡Datos guardados con éxito!\n");
                pausa();
                break;

            case 1: // Mostrar matrices
                limpiarPantalla();
                if (!datosIngresados) {
                    printf("Primero debe ingresar los datos (Opcion 1).\n");
                } else {
                    imprimirMatriz(maquinaA, "Maquina A");
                    imprimirMatriz(maquinaB, "Maquina B");
                }
                pausa();
                break;

            case 2: // Comparar suma
                limpiarPantalla();
                if (!datosIngresados) {
                    printf("Primero debe ingresar los datos (Opcion 1).\n");
                } else {
                    int sumaA = sumarElementos(maquinaA);
                    int sumaB = sumarElementos(maquinaB);
                    printf("Suma Maquina A: %d\n", sumaA);
                    printf("Suma Maquina B: %d\n\n", sumaB);
                    
                    if (sumaA > sumaB) printf("La Maquina A tiene la mayor suma total.\n");
                    else if (sumaB > sumaA) printf("La Maquina B tiene la mayor suma total.\n");
                    else printf("Ambas maquinas tienen la misma suma total.\n");
                }
                pausa();
                break;

            case 3: // Promedios
                limpiarPantalla();
                if (!datosIngresados) {
                    printf("Primero debe ingresar los datos (Opcion 1).\n");
                } else {
                    printf("Promedio Maquina A: %.2f\n", promedioMatriz(maquinaA));
                    printf("Promedio Maquina B: %.2f\n", promedioMatriz(maquinaB));
                }
                pausa();
                break;

            case 4: // Máximos y Mínimos
                limpiarPantalla();
                if (!datosIngresados) {
                    printf("Primero debe ingresar los datos (Opcion 1).\n");
                } else {
                    printf("Maquina A -> Maximo: %d | Minimo: %d\n", buscarMayor(maquinaA), buscarMenor(maquinaA));
                    printf("Maquina B -> Maximo: %d | Minimo: %d\n", buscarMayor(maquinaB), buscarMenor(maquinaB));
                }
                pausa();
                break;

            case 5: // Contar Pares
                limpiarPantalla();
                if (!datosIngresados) {
                    printf("Primero debe ingresar los datos (Opcion 1).\n");
                } else {
                    printf("Cantidad de pares en Maquina A: %d\n", contarPares(maquinaA));
                    printf("Cantidad de pares en Maquina B: %d\n", contarPares(maquinaB));
                }
                pausa();
                break;

            case 6: // Salir o Tecla ESC
            case -1:
                limpiarPantalla();
                printf("Saliendo del programa...\n");
                return 0;
        }
    } while(1);

    return 0;
}

// --- FUNCIONES INTERACTIVAS Y DE INTERFAZ ---

void limpiarPantalla() {
    system("cls");
}

void pausa() {
    printf("\nPresione cualquier tecla para continuar...");
    _getch();
}

int menuNavegable(const char *opciones[], int numOpciones) {
    int seleccion = 0;
    int tecla;

    while (1) {
        limpiarPantalla();
        printf("=== MENU PRINCIPAL INTERACTIVO ===\n");
        printf("(Usa las flechas ARRIBA/ABAJO para navegar, ENTER para seleccionar, ESC para salir)\n\n");

        for (int i = 0; i < numOpciones; i++) {
            if (i == seleccion) {
                printf("  -> [ %s ]\n", opciones[i]);
            } else {
                printf("     %s  \n", opciones[i]);
            }
        }

        tecla = _getch();
        if (tecla == ESC) return -1;

        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            if (tecla == FLECHA_ARRIBA) {
                seleccion = (seleccion - 1 + numOpciones) % numOpciones;
            } else if (tecla == FLECHA_ABAJO) {
                seleccion = (seleccion + 1) % numOpciones;
            }
        } else if (tecla == ENTER) {
            return seleccion;
        }
    }
}

void ingresarDatosInteractivo(int matriz[TAM][TAM], char *nombre) {
    int posX = 0, posY = 0;
    int tecla;

    while (1) {
        limpiarPantalla();
        printf("--- Edicion de datos: %s ---\n", nombre);
        printf("(Muevete con FLECHAS | ENTER: Modificar valor | ESC: Guardar y Volver)\n\n");

        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (i == posX && j == posY) {
                    printf("[%3d] ", matriz[i][j]);
                } else {
                    printf(" %3d  ", matriz[i][j]);
                }
            }
            printf("\n");
        }

        printf("\nPosicion actual: (%d, %d) = %d\n", posX + 1, posY + 1, matriz[posX][posY]);

        tecla = _getch();
        if (tecla == ESC) break;

        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            switch (tecla) {
                case FLECHA_ARRIBA:    if (posX > 0) posX--; break;
                case FLECHA_ABAJO:     if (posX < TAM - 1) posX++; break;
                case FLECHA_IZQUIERDA: if (posY > 0) posY--; break;
                case FLECHA_DERECHA:   if (posY < TAM - 1) posY++; break;
            }
        } else if (tecla == ENTER) {
            printf("\nIngrese nuevo valor para [%d][%d]: ", posX + 1, posY + 1);
            scanf("%d", &matriz[posX][posY]);
            while (getchar() != '\n'); // Limpiar buffer de entrada
        }
    }
}

// --- FUNCIONES LOGICAS (ORIGINALES) ---

void imprimirMatriz(int matriz[TAM][TAM], char *nombre) {
    printf("--- Matriz: %s ---\n", nombre);
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%5d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int sumarElementos(int matriz[TAM][TAM]) {
    int suma = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            suma += matriz[i][j];
        }
    }
    return suma;
}

double promedioMatriz(int matriz[TAM][TAM]) {
    return (double)sumarElementos(matriz) / (TAM * TAM);
}

int buscarMayor(int matriz[TAM][TAM]) {
    int mayor = matriz[0][0];
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (matriz[i][j] > mayor) mayor = matriz[i][j];
        }
    }
    return mayor;
}

int buscarMenor(int matriz[TAM][TAM]) {
    int menor = matriz[0][0];
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (matriz[i][j] < menor) menor = matriz[i][j];
        }
    }
    return menor;
}

int contarPares(int matriz[TAM][TAM]) {
    int contador = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (matriz[i][j] % 2 == 0) contador++;
        }
    }
    return contador;
}
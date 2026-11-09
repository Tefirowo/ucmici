/*

Backtrack tarea 1.5 U2
Ignacia C
Benjamin C

*/
#include <stdio.h>

#define FIL 5
#define COL 5

int laberinto[FIL][COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 1, 9}
};

void implab(){

    for(int i=0; i<5; i++){

            for(int k=0; k<5; k++){

                printf("%d ", laberinto[i][k]);

            }
            printf("\n");
    }
}

int solucion[FIL][COL]; /* marca el camino elegido */

void imprimirSolucion(void) {
    int i, j;
    printf("\nCamino encontrado:\n");
    for (i = 0; i < FIL; i++) {
        for (j = 0; j < COL; j++) {
            if (solucion[i][j])
                printf("*");
            else if (laberinto[i][j] == 1)
                printf(" # ");
            else if (laberinto[i][j] == 9)
                printf(" 9 ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

int resolver(int f, int c) {
    // 1. Caso base: si estamos fuera de los límites de la matriz
    if (f < 0 || f >= FIL || c < 0 || c >= COL) {
        return 0;
    }

    // 2. Caso base: si es una pared (1) o ya visitamos esta casilla en este camino (solucion == 1)
    if (laberinto[f][c] == 1 || solucion[f][c] == 1) {
        return 0;
    }

    // 3. Caso base de éxito: si encontramos la meta (9)
    if (laberinto[f][c] == 9) {
        solucion[f][c] = 1; // Marcamos también la meta en la solución
        return 1;
    }

    // 4. Marcar la celda actual como parte del camino elegido
    solucion[f][c] = 1;

    // 5. Probar los 4 movimientos recursivamente (Abajo, Arriba, Derecha, Izquierda)
    if (resolver(f + 1, c)) return 1; // Intentar abajo
    if (resolver(f - 1, c)) return 1; // Intentar arriba
    if (resolver(f, c + 1)) return 1; // Intentar derecha
    if (resolver(f, c - 1)) return 1; // Intentar izquierda

    // 6. 🧀 ABORTAR MISIÓN 🐁!!!   Si ninguna de las 4 direcciones funcionó, deshacemos:
    solucion[f][c] = 0; 
    
    return 0; // Retornamos 0 indicando que por aquí no era
}

int main(void) {

    // implab(); // Para testear, descomentar para imprimir el laberinto original
    
    if (resolver(0, 0)) {
        imprimirSolucion();
    } else {
        printf("\nNo hay salida\n");
    }

    

    
    return 0;
}
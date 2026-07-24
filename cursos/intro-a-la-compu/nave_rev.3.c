/* ============================================================
 *  MONITOREANDO LA NAVE ESPACIAL
 *  Introduccion a la Computacion - 2026
 *  Estandar: ANSI C89
 *  ============================================================ */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DIM 30
#define MAX_OBJ (MAX_DIM * MAX_DIM)
#define MAX_ORDENES 420

#define LLEGAMOS_SALVO 0
#define NAVE_PERDIDA   1
#define NAVE_DESTRUIDA 2

#define ORIENT_N 0
#define ORIENT_E 1
#define ORIENT_S 2
#define ORIENT_O 3

/* Iniciar funciones :p, funciones indentadas btw, para poder leerlas mas fácil */
int leerDatos(const char *nombreArchivo,
              int *filasTablero, int *columnasTablero,
              int *naveFilaInicio, int *naveColumnaInicio,
              int *destinoFila, int *destinoColumna,
              int estrellasFilas[], int estrellasColumnas[], int *cantidadEstrellas,
              int destructoresFilas[], int destructoresColumnas[], int *cantidadDestructores,
              int *orientacionNave,
              int *cantidadOrdenes, char secuenciaOrdenes[]);

int hayPeligro(int filaEvaluar, int columnaEvaluar,
               int estrellasFilas[], int estrellasColumnas[], int cantidadEstrellas,
               int destructoresFilas[], int destructoresColumnas[], int cantidadDestructores);

int seguirRuta(int filasTablero, int columnasTablero,
               int naveFilaInicio, int naveColumnaInicio,
               int destinoFila, int destinoColumna,
               int estrellasFilas[], int estrellasColumnas[], int cantidadEstrellas,
               int destructoresFilas[], int destructoresColumnas[], int cantidadDestructores,
               int orientacionNave,
               int cantidadOrdenes, char secuenciaOrdenes[]);

void generarSalida(const char *nombreArchivo, int situacionFinal);


/* Main jeje*/
int main()
{
    int filasTablero, columnasTablero;
    int naveFilaInicio, naveColumnaInicio;
    int destinoFila, destinoColumna;
    int estrellasFilas[MAX_OBJ], estrellasColumnas[MAX_OBJ], cantidadEstrellas;
    int destructoresFilas[MAX_OBJ], destructoresColumnas[MAX_OBJ], cantidadDestructores;
    int orientacionNave;
    int cantidadOrdenes;
    char secuenciaOrdenes[MAX_ORDENES];
    int resultadoSituacion;
    int lecturaExitosa;
    
    lecturaExitosa = leerDatos("situacion_inicial.txt",
                               &filasTablero, &columnasTablero,
                               &naveFilaInicio, &naveColumnaInicio,
                               &destinoFila, &destinoColumna,
                               estrellasFilas, estrellasColumnas, &cantidadEstrellas,
                               destructoresFilas, destructoresColumnas, &cantidadDestructores,
                               &orientacionNave,
                               &cantidadOrdenes, secuenciaOrdenes);
    
    if (!lecturaExitosa) {
        printf("Error: no se pudo abrir situacion_inicial.txt\n");
        return 1;
    }
    
    resultadoSituacion = seguirRuta(filasTablero, columnasTablero,
                                    naveFilaInicio, naveColumnaInicio,
                                    destinoFila, destinoColumna,
                                    estrellasFilas, estrellasColumnas, cantidadEstrellas,
                                    destructoresFilas, destructoresColumnas, cantidadDestructores,
                                    orientacionNave,
                                    cantidadOrdenes, secuenciaOrdenes);
    
    generarSalida("situacion_final.txt", resultadoSituacion);
    
    return 0;
}


/* Funciones funcionando */

int leerDatos(const char *nombreArchivo,
              int *filasTablero, int *columnasTablero,
              int *naveFilaInicio, int *naveColumnaInicio,
              int *destinoFila, int *destinoColumna,
              int estrellasFilas[], int estrellasColumnas[], int *cantidadEstrellas,
              int destructoresFilas[], int destructoresColumnas[], int *cantidadDestructores,
              int *orientacionNave,
              int *cantidadOrdenes, char secuenciaOrdenes[])
{
    FILE *archivoEntrada;
    int indice;
    char caracterOrientacion;
    char caracterOrden;
    
    archivoEntrada = fopen(nombreArchivo, "r");
    if (archivoEntrada == NULL) {
        return 0;
    }
    
    fscanf(archivoEntrada, "%d %d", filasTablero, columnasTablero);
    fscanf(archivoEntrada, "%d %d", naveFilaInicio, naveColumnaInicio);
    fscanf(archivoEntrada, "%d %d", destinoFila, destinoColumna);
    
    fscanf(archivoEntrada, "%d", cantidadEstrellas);
    for (indice = 0; indice < *cantidadEstrellas; indice++) {
        fscanf(archivoEntrada, "%d %d", &estrellasFilas[indice], &estrellasColumnas[indice]);
    }
    
    fscanf(archivoEntrada, "%d", cantidadDestructores);
    for (indice = 0; indice < *cantidadDestructores; indice++) {
        fscanf(archivoEntrada, "%d %d", &destructoresFilas[indice], &destructoresColumnas[indice]);
    }
    
    /* lee la letra de orientacion, saltando espacios/saltos de linea */
    fscanf(archivoEntrada, " %c", &caracterOrientacion);
    if (caracterOrientacion == 'N') {
        *orientacionNave = ORIENT_N;
    } else if (caracterOrientacion == 'E') {
        *orientacionNave = ORIENT_E;
    } else if (caracterOrientacion == 'S') {
        *orientacionNave = ORIENT_S;
    } else {
        *orientacionNave = ORIENT_O;
    }
    
    fscanf(archivoEntrada, "%d", cantidadOrdenes);
    
    /* lee la secuencia de ordenes (letras pegadas, sin espacios) */
    fscanf(archivoEntrada, " "); /* descarta el salto de linea pendiente */
    for (indice = 0; indice < *cantidadOrdenes; indice++) {
        fscanf(archivoEntrada, "%c", &caracterOrden);
        secuenciaOrdenes[indice] = caracterOrden;
    }
    secuenciaOrdenes[*cantidadOrdenes] = '\0';
    
    fclose(archivoEntrada);
    return 1;
}

/* Revisa si existe una estrella o destructor en la posicion */

int hayPeligro(int filaEvaluar, int columnaEvaluar,
               int estrellasFilas[], int estrellasColumnas[], int cantidadEstrellas,
               int destructoresFilas[], int destructoresColumnas[], int cantidadDestructores)
{
    int indice;
    
    for (indice = 0; indice < cantidadEstrellas; indice++) {
        if (estrellasFilas[indice] == filaEvaluar && estrellasColumnas[indice] == columnaEvaluar) {
            return 1;
        }
    }
    for (indice = 0; indice < cantidadDestructores; indice++) {
        if (destructoresFilas[indice] == filaEvaluar && destructoresColumnas[indice] == columnaEvaluar) {
            return 1;
        }
    }
    return 0;
}

/* Verificar si el recorrido dicho en el archivo funciona */
int seguirRuta(int filasTablero, int columnasTablero,
               int naveFilaInicio, int naveColumnaInicio,
               int destinoFila, int destinoColumna,
               int estrellasFilas[], int estrellasColumnas[], int cantidadEstrellas,
               int destructoresFilas[], int destructoresColumnas[], int cantidadDestructores,
               int orientacionNave,
               int cantidadOrdenes, char secuenciaOrdenes[])
{
    int indice;
    int filaActual, columnaActual;
    int desplazamientoFila, desplazamientoColumna;
    int proximaFila, proximaColumna;
    
    filaActual = naveFilaInicio;
    columnaActual = naveColumnaInicio;
    
    /* si la nave parte sobre un destructor o estrella, queda destruida */
    if (hayPeligro(filaActual, columnaActual, estrellasFilas, estrellasColumnas, cantidadEstrellas,
        destructoresFilas, destructoresColumnas, cantidadDestructores)) {
        return NAVE_DESTRUIDA;
        }
        
        for (indice = 0; indice < cantidadOrdenes; indice++) {
            if (secuenciaOrdenes[indice] == 'I') {
                orientacionNave = (orientacionNave + 3) % 4; /* giro antihorario */
            } else if (secuenciaOrdenes[indice] == 'D') {
                orientacionNave = (orientacionNave + 1) % 4; /* giro horario */
            } else if (secuenciaOrdenes[indice] == 'A') {
                desplazamientoFila = 0;
                desplazamientoColumna = 0;
                if (orientacionNave == ORIENT_N) {
                    desplazamientoFila = -1;
                } else if (orientacionNave == ORIENT_E) {
                    desplazamientoColumna = 1;
                } else if (orientacionNave == ORIENT_S) {
                    desplazamientoFila = 1;
                } else {
                    desplazamientoColumna = -1;
                }
                
                proximaFila = filaActual + desplazamientoFila;
                proximaColumna = columnaActual + desplazamientoColumna;
                
                /* avanzar fuera de los limites del recinto */
                if (proximaFila < 0 || proximaFila >= filasTablero || proximaColumna < 0 || proximaColumna >= columnasTablero) {
                    return NAVE_DESTRUIDA;
                }
                
                filaActual = proximaFila;
                columnaActual = proximaColumna;
                
                if (hayPeligro(filaActual, columnaActual, estrellasFilas, estrellasColumnas, cantidadEstrellas,
                    destructoresFilas, destructoresColumnas, cantidadDestructores)) {
                    return NAVE_DESTRUIDA;
                    }
            }
        }
        
        if (filaActual == destinoFila && columnaActual == destinoColumna) {
            return LLEGAMOS_SALVO;
        }
        return NAVE_PERDIDA;
}

/* Generar archivo :3 */
void generarSalida(const char *nombreArchivo, int situacionFinal)
{
    FILE *archivoSalida;
    
    archivoSalida = fopen(nombreArchivo, "w");
    if (archivoSalida == NULL) {
        return;
    }
    
    if (situacionFinal == LLEGAMOS_SALVO) {
        fprintf(archivoSalida, "Llegamos a salvo\n");
    } else if (situacionFinal == NAVE_DESTRUIDA) {
        fprintf(archivoSalida, "Nave destruida\n");
    } else {
        fprintf(archivoSalida, "Nave perdida\n");
    }
    
    fclose(archivoSalida);
}

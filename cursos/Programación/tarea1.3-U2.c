/*
Programación S1
Docente: Profesor Luis Ponce Rosales
Ignacia Carrera - Benjamin Castillo
Calculadora corte
*/

#include <stdio.h>

#define MAX_PIEZAS 20

/* Declaración de prototipos */
float calcularArea(float ancho, float alto);
float calcularAreaTotal(float anchos[], float altos[], int n);
float calcularAprovechamiento(float areaPiezas, float areaPlaca);
void mostrarReporte(float areaPlaca, float areaPiezas, float areaDesperdicio, float porcentaje);
void mostrarRecomendacion(float porcentaje);

int main() {
    float anchoPlaca, altoPlaca;
    int numPiezas;
    
    /* Arreglos paralelos tamaños de piezas */
    float anchosPiezas[MAX_PIEZAS];
    float altosPiezas[MAX_PIEZAS];

    printf("=== CALCULADORA DE OPTIMIZACIÓN DE CORTE PULENTA ===\n\n");

    /* 1. Solicitar dimensiones de la placa */
    printf("Ingrese el ancho de la placa (mm): ");
    scanf("%f", &anchoPlaca);
    printf("Ingrese el alto de la placa (mm): ");
    scanf("%f", &altoPlaca);

    /* 2. Solicitar cantidad de piezas con validación (máximo 20) */
    do {
        printf("\nIngrese la cantidad de piezas a cortar (1 a %d): ", MAX_PIEZAS);
        scanf("%d", &numPiezas);
        if (numPiezas <= 0 || numPiezas > MAX_PIEZAS) {
            printf("Error: La cantidad de piezas debe estar entre 1 y %d.\n", MAX_PIEZAS);
        }
    } while (numPiezas <= 0 || numPiezas > MAX_PIEZAS);

    /* 3. Solicitar las dimensiones de cada pieza */
    printf("\n--- Entrada de datos para las piezas ---\n");
    for (int i = 0; i < numPiezas; i++) {
        printf("\nPieza #%d:\n", i + 1);
        printf("  Ancho (mm): ");
        scanf("%f", &anchosPiezas[i]);
        printf("  Alto (mm): ");
        scanf("%f", &altosPiezas[i]);
    }

    /* 4. Cálculos mediante las funciones */
    float areaPlaca = calcularArea(anchoPlaca, altoPlaca);
    float areaPiezas = calcularAreaTotal(anchosPiezas, altosPiezas, numPiezas);
    float areaDesperdicio = areaPlaca - areaPiezas;
    float porcentaje = calcularAprovechamiento(areaPiezas, areaPlaca);

    /* 5. Mostrar reporte final y recomendaciones */
    mostrarReporte(areaPlaca, areaPiezas, areaDesperdicio, porcentaje);

    return 0;
}

/* Función para calcular el área de un rectángulo */
float calcularArea(float ancho, float alto) {
    return ancho * alto;
}

/* Función para calcular el área total sumando cada par de dimensiones */
float calcularAreaTotal(float anchos[], float altos[], int n) {
    float areaTotal = 0.0f;
    for (int i = 0; i < n; i++) {
        areaTotal += calcularArea(anchos[i], altos[i]);
    }
    return areaTotal;
}

/* Función para calcular el porcentaje de aprovechamiento */
float calcularAprovechamiento(float areaPiezas, float areaPlaca) {
    if (areaPlaca == 0.0f) {
        return 0.0f;
    }
    return (areaPiezas / areaPlaca) * 100.0f;
}

/* Función para imprimir el reporte de resultados */
void mostrarReporte(float areaPlaca, float areaPiezas, float areaDesperdicio, float porcentaje) {
    printf("\n=========================================\n");
    printf("            REPORTE DE CORTE             \n");
    printf("=========================================\n");
    printf("Área total de la placa:    %.2f mm²\n", areaPlaca);
    printf("Área total de las piezas:  %.2f mm²\n", areaPiezas);
    printf("Área desperdiciada:        %.2f mm²\n", areaDesperdicio);
    printf("Porcentaje aprovechado:    %.2f%%\n", porcentaje);
    printf("-----------------------------------------\n");
    printf("Recomendación: ");
    mostrarRecomendacion(porcentaje);
    printf("=========================================\n");
}

/* Función para determinar y mostrar la recomendación según el porcentaje. También avisar si el corte supera la cantidad de material disponible */
void mostrarRecomendacion(float porcentaje) {
    if (porcentaje >= 101.0f) {
        printf("Te pasaste miloco, no te alcanza el material\n");
    } else if (porcentaje >= 85.0f) {
        printf("Corte óptimo\n");
    } else if (porcentaje >= 70.0f && porcentaje < 85.0f) {
        printf("Corte aceptable, revisar distribución\n");
    } else {
        printf("Alto desperdicio, reconsiderar piezas\n");
    }
}
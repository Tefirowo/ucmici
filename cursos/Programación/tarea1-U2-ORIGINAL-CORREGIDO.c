#include <stdio.h>
#include <math.h>

/* Prototipos */
float leer_numero(void);
float calcular_area_circulo(float radio);
void imprimir_resultado(float area);
float potencia_cuadrada(float x);
int es_positivo(float x);

int main(void) {
    float r, area;
    r = leer_numero();
    if (es_positivo(r)) {
        area = calcular_area_circulo(r);
        imprimir_resultado(area);
    } else {
        printf("Error: el radio debe ser positivo.\n");
    }
    return 0;
}

float leer_numero(void) {
    float valor;
    printf("Ingrese el radio: ");
    scanf("%f", &valor);
    return valor;
}

int es_positivo(float x) {
    return x > 0;
}

float potencia_cuadrada(float x) {
    return x * x;
}

float calcular_area_circulo(float radio) {
    return 3.14159f * potencia_cuadrada(radio);
}

void imprimir_resultado(float area) {
    printf("El área es: %.2f\n", area);
}
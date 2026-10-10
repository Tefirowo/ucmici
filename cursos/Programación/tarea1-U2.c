#include <stdio.h>

/* Prototipos bacanes*/
int leer_horas(void);
float leer_valor_hora(void);
float calcular_bruto(int horas, float valor_hora);
float calcular_descuento(float bruto);
float calcular_neto(float bruto, float descuento);
void mostrar_resultados(float bruto, float descuento, float neto);

int main(void) {
    int horas = leer_horas();
    float valor_hora = leer_valor_hora();
    float bruto = calcular_bruto(horas, valor_hora);
    float descuento = calcular_descuento(bruto);
    float neto = calcular_neto(bruto, descuento);

    mostrar_resultados(bruto, descuento, neto);
    return 0;
}

/* 
 * Propósito: Leer horas trabajadas por teclado.
 * Precondición: Ninguna.
 * Postcondición: Retorna un entero >= 0.
 */
int leer_horas(void) {
    int h;
    printf("Ingrese horas trabajadas: ");
    scanf("%d", &h);
    return h;
}

/* 
 * Propósito: Leer el valor pactado por hora.
 * Precondición: Ninguna.
 * Postcondición: Retorna el valor en float.
 */
float leer_valor_hora(void) {
    float v;
    printf("Ingrese valor hora: ");
    scanf("%f", &v);
    return v;
}

/* 
 * Propósito: Calcular el sueldo bruto.
 * Precondición: horas >= 0, valor_hora >= 0.
 * Postcondición: Retorna horas * valor_hora.
 */
float calcular_bruto(int horas, float valor_hora) {
    return (float)horas * valor_hora;
}

/* 
 * Propósito: Calcular el descuento según tramos.
 * Precondición: bruto >= 0.
 * Postcondición: Retorna el monto a descontar.
 */
float calcular_descuento(float bruto) {
    if (bruto < 500000.0f) {
        return bruto * 0.05f;
    } else if (bruto < 1000000.0f) {
        return bruto * 0.10f;
    } else {
        return bruto * 0.15f;
    }
}

/* 
 * Propósito: Calcular el sueldo neto final.
 * Precondición: bruto >= 0, descuento >= 0.
 * Postcondición: Retorna la diferencia (bruto - descuento).
 */
float calcular_neto(float bruto, float descuento) {
    return bruto - descuento;
}

/* 
 * Propósito: Mostrar en pantalla los resultados.
 * Precondición: Recibe valores numéricos válidos.
 * Postcondición: Despliega bruto, descuento y neto.
 */
void mostrar_resultados(float bruto, float descuento, float neto) {
    printf("\n--- RESUMEN DE SUELDO ---\n");
    printf("Sueldo Bruto: $%.2f\n", bruto);
    printf("Descuento:    $%.2f\n", descuento);
    printf("Sueldo Neto:  $%.2f\n", neto);
}
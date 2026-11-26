#include <stdio.h>
#include <assert.h>
#include <limits.h>

int pruebas_pasadas = 0;
int pruebas_fallidas = 0;

void verificar(int condicion, const char *mensaje) {
    if (condicion) {
        pruebas_pasadas++;
        printf(" [OK] %s\n", mensaje);
    } else {
        pruebas_fallidas++;
        printf(" [FALLO] %s\n", mensaje);
    }
}

/* Funcion pura */
int maximo_tres(int a, int b, int c) {
    int maximo = a;

    if (b > maximo) {
        maximo = b;
    }
    if (c > maximo) {
        maximo = c;
    }
    return maximo;
}

/* Modifica las variables apuntadas */
void intercambiar(int *x, int *y) {
    int temp;

    assert(x != 0);
    assert(y != 0);
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Invierte el arreglo in-place */
void invertir_arreglo(int arr[], int n) {
    int i;
    int temp;

    assert(arr != 0 || n == 0);
    assert(n >= 0);
    for (i = 0; i < n / 2; i++) {
        temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

int arreglo_igual(const int arr[], const int esperado[], int n) {
    int i;

    for (i = 0; i < n; i++) {
        if (arr[i] != esperado[i]) {
            return 0;
        }
    }
    return 1;
}

void test_maximo_tres(void) {
    printf("Pruebas: maximo_tres\n");
    verificar(maximo_tres(5, 3, 8) == 8,
              "MT01 - valor normal: el tercero es el maximo");
    verificar(maximo_tres(9, 4, 2) == 9,
              "MT02 - limite: el primero es el maximo");
    verificar(maximo_tres(-2, -7, -1) == -1,
              "MT03 - negativos: el menor negativo es el maximo");
    verificar(maximo_tres(5, 5, 5) == 5,
              "MT04 - valores iguales");
    verificar(maximo_tres(0, 0, 0) == 0,
              "MT05 - limite cero");
    verificar(maximo_tres(INT_MIN, 0, INT_MAX) == INT_MAX,
              "MT06 - extremos de int");
}

void test_intercambiar(void) {
    int x;
    int y;

    printf("\nPruebas: intercambiar\n");

    x = 5;
    y = 9;
    intercambiar(&x, &y);
    verificar(x == 9 && y == 5,
              "INT01 - valores normales intercambiados");

    x = 7;
    y = 7;
    intercambiar(&x, &y);
    verificar(x == 7 && y == 7,
              "INT02 - valores iguales");

    x = 0;
    y = 4;
    intercambiar(&x, &y);
    verificar(x == 4 && y == 0,
              "INT03 - limite cero");

    x = -3;
    y = -8;
    intercambiar(&x, &y);
    verificar(x == -8 && y == -3,
              "INT04 - negativos");

    x = -1;
    y = 1;
    intercambiar(&x, &y);
    verificar(x == 1 && y == -1,
              "INT05 - negativo y positivo");

    x = INT_MAX;
    y = INT_MIN;
    intercambiar(&x, &y);
    verificar(x == INT_MIN && y == INT_MAX,
              "INT06 - extremos de int");
}

void test_invertir_arreglo(void) {
    int arreglo[6];
    int esperado[6];

    printf("\nPruebas: invertir_arreglo\n");

    arreglo[0] = 1;
    arreglo[1] = 2;
    arreglo[2] = 3;
    arreglo[3] = 4;
    esperado[0] = 4;
    esperado[1] = 3;
    esperado[2] = 2;
    esperado[3] = 1;
    invertir_arreglo(arreglo, 4);
    verificar(arreglo_igual(arreglo, esperado, 4),
              "INV01 - arreglo normal");

    arreglo[0] = 7;
    invertir_arreglo(arreglo, 1);
    verificar(arreglo[0] == 7,
              "INV02 - limite: un elemento");

    arreglo[0] = 123;
    invertir_arreglo(arreglo, 0);
    verificar(arreglo[0] == 123,
              "INV03 - limite: arreglo de tamano cero");

    arreglo[0] = -3;
    arreglo[1] = -2;
    arreglo[2] = -1;
    esperado[0] = -1;
    esperado[1] = -2;
    esperado[2] = -3;
    invertir_arreglo(arreglo, 3);
    verificar(arreglo_igual(arreglo, esperado, 3),
              "INV04 - numeros negativos");

    arreglo[0] = 5;
    arreglo[1] = 5;
    arreglo[2] = 5;
    arreglo[3] = 5;
    esperado[0] = 5;
    esperado[1] = 5;
    esperado[2] = 5;
    esperado[3] = 5;
    invertir_arreglo(arreglo, 4);
    verificar(arreglo_igual(arreglo, esperado, 4),
              "INV05 - valores iguales");

    arreglo[0] = 0;
    arreglo[1] = -2;
    arreglo[2] = 8;
    arreglo[3] = -5;
    esperado[0] = -5;
    esperado[1] = 8;
    esperado[2] = -2;
    esperado[3] = 0;
    invertir_arreglo(arreglo, 4);
    verificar(arreglo_igual(arreglo, esperado, 4),
              "INV06 - ceros y negativos");

    arreglo[0] = INT_MAX;
    arreglo[1] = INT_MIN;
    arreglo[2] = 0;
    esperado[0] = 0;
    esperado[1] = INT_MIN;
    esperado[2] = INT_MAX;
    invertir_arreglo(arreglo, 3);
    verificar(arreglo_igual(arreglo, esperado, 3),
              "INV07 - extremos de int");
}

int main(void) {
    printf("=== Iniciando pruebas unitarias ===\n\n");

    test_maximo_tres();
    test_intercambiar();
    test_invertir_arreglo();

    printf("\n=== Resumen ===\n");
    printf("Pasadas: %d\n", pruebas_pasadas);
    printf("Fallidas: %d\n", pruebas_fallidas);

    return (pruebas_fallidas == 0) ? 0 : 1;
}

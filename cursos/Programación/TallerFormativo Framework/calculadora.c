#include "calculadora.h"
#include <string.h>

int sumar(int a, int b)
{
    return a + b;
}

int restar(int a, int b)
{
    /* ERROR intencionado: deberia ser a - b */
    return a + b;
}

int dividir(int a, int b)
{
    /* ERROR intencionado: no se comprueba b == 0 */
    return a / b;
}

int es_palindromo(const char *s)
{
    int i, j;
    if (s == NULL) {
        return 0;
    }
    i = 0;
    j = (int)strlen(s) - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}
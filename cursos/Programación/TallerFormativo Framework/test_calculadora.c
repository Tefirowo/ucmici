#include <stdio.h>
#include "minitest.h"
#include "calculadora.h"

static void test_sumar(void)
{
    /* Arrange & Act & Assert */
    MT_ASSERT_EQ_INT(5, sumar(2, 3));    /* caso normal */
    MT_ASSERT_EQ_INT(0, sumar(0, 0));    /* frontera */
    MT_ASSERT_EQ_INT(-1, sumar(2, -3));  /* signos opuestos */
    MT_ASSERT_EQ_INT(-5, sumar(-2, -3)); /* negativos */
}

static void test_restar(void)
{
    MT_ASSERT_EQ_INT(-1, restar(2, 3));  /* caso normal */
    MT_ASSERT_EQ_INT(0, restar(0, 0));   /* frontera */
    MT_ASSERT_EQ_INT(5, restar(2, -3));  /* signos opuestos */
    MT_ASSERT_EQ_INT(1, restar(-2, -3)); /* negativos */
}

static void test_dividir(void)
{
    MT_ASSERT_EQ_INT(2, dividir(6, 3));   /* caso normal */
    MT_ASSERT_EQ_INT(0, dividir(0, 5));   /* cero entre algo */
    MT_ASSERT_EQ_INT(-2, dividir(-6, 3)); /* numerador negativo */
    MT_ASSERT_EQ_INT(-1, dividir(5, 0));  /* division por cero -> error */
}

static void test_es_palindromo(void)
{
    MT_ASSERT_EQ_INT(1, es_palindromo("oso"));
    MT_ASSERT_EQ_INT(1, es_palindromo("a"));
    MT_ASSERT_EQ_INT(1, es_palindromo(""));
    MT_ASSERT_EQ_INT(0, es_palindromo("casa"));
    MT_ASSERT_EQ_INT(0, es_palindromo(NULL)); /* frontera: NULL */
}

int main(void)
{
    MT_INIT();
    test_sumar();
    test_restar();
    test_dividir();
    test_es_palindromo();
    MT_REPORT();
    return mt_fallos; /* 0 = todas OK, !=0 = alguna fallo */
}
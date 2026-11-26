#ifndef MINITEST_H
#define MINITEST_H

#include <stdio.h>

/* Contadores globales (definidos en minitest.c) */
extern int mt_total;
extern int mt_fallos;

void mt_assert_eq_int(int esperado, int obtenido, const char *archivo, int linea);

#define MT_INIT() do { mt_total = 0; mt_fallos = 0; } while (0)

#define MT_ASSERT_EQ_INT(esperado, obtenido) \
    mt_assert_eq_int((esperado), (obtenido), __FILE__, __LINE__)

#define MT_ASSERT_TRUE(cond)                                          \
    do {                                                              \
        mt_total++;                                                   \
        if (!(cond)) {                                                \
            mt_fallos++;                                              \
            printf("FALLO en %s:%d -> condicion falsa: %s\n",         \
                   __FILE__, __LINE__, #cond);                        \
        }                                                             \
    } while (0)

#define MT_REPORT()                                                   \
    do {                                                              \
        printf("\n--- RESULTADOS ---\n");                             \
        printf("Pruebas ejecutadas: %d\n", mt_total);                 \
        printf("Pruebas fallidas : %d\n", mt_fallos);                 \
        if (mt_fallos == 0) {                                         \
            printf("ESTADO: OK\n");                                   \
        } else {                                                      \
            printf("ESTADO: FALLO\n");                                \
        }                                                             \
    } while (0)

#endif /* MINITEST_H */
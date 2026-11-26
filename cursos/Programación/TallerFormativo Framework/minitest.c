#include "minitest.h"

int mt_total = 0;
int mt_fallos = 0;

void mt_assert_eq_int(int esperado, int obtenido, const char *archivo, int linea)
{
    mt_total++;
    if (esperado != obtenido) {
        mt_fallos++;
        printf("FALLO en %s:%d -> esperado %d, obtenido %d\n",
               archivo, linea, esperado, obtenido);
    }
}
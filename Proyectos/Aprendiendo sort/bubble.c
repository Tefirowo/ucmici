/*

CON LINUX: gcc bubble.c -o bubble_raylib -lraylib -lm -lpthread -ldl -lrt -lX11


*/


#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define TAM 20
#define ANCHO_VENTANA 900
#define ALTO_VENTANA 550

typedef struct {
    int datos[TAM];
    int original[TAM];
    int i;
    int j;
    int activo_a;
    int activo_b;cd 
    int terminado;
    int pausado;
    float tiempo_acumulado;
    float intervalo;
} ContextoSort;

/* Prototipos de funciones */
int leer_entero_seguro(const char *prompt, int *salida);
void leer_valores(int arr[], int n);
void copiar_valores(const int origen[], int destino[], int n);
void reiniciar_contexto(ContextoSort *ctx);
void intercambiar(int *a, int *b);
int maximo_arreglo(const int arr[], int n);
void ejecutar_paso_sort(ContextoSort *ctx, int n);
void actualizar_animacion(ContextoSort *ctx, float dt, int n);
void renderizar(const ContextoSort *ctx, int n);

int main(void) {
    ContextoSort ctx;
    int i;

    printf("Con tamano %d\n", TAM);
    leer_valores(ctx.original, TAM);

    printf("Metiste estos valores:\n");
    for (i = 0; i < TAM; i++) {
        printf("%d\n", ctx.original[i]);
    }

    ctx.intervalo = 0.25f;
    reiniciar_contexto(&ctx);

    InitWindow(ANCHO_VENTANA, ALTO_VENTANA, "Bubble Sort - Raylib (C)");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_R)) {
            reiniciar_contexto(&ctx);
        }

        if (IsKeyPressed(KEY_SPACE)) {
            ctx.pausado = !ctx.pausado;
        }

        if (IsKeyPressed(KEY_UP)) {
            ctx.intervalo -= 0.05f;
            if (ctx.intervalo < 0.03f) {
                ctx.intervalo = 0.03f;
            }
        }

        if (IsKeyPressed(KEY_DOWN)) {
            ctx.intervalo += 0.05f;
            if (ctx.intervalo > 1.50f) {
                ctx.intervalo = 1.50f;
            }
        }

        actualizar_animacion(&ctx, dt, TAM);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        renderizar(&ctx, TAM);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

int leer_entero_seguro(const char *prompt, int *salida) {
    char buffer[128];
    char *fin;
    long valor;

    while (1) {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0;
        }

        errno = 0;
        valor = strtol(buffer, &fin, 10);

        if (fin == buffer) {
            printf("Entrada invalida: ingresa un numero entero.\n");
            continue;
        }

        while (*fin != '\0' && isspace((unsigned char)*fin)) {
            fin++;
        }

        if (*fin != '\0') {
            printf("Entrada invalida: no se permiten letras ni decimales.\n");
            continue;
        }

        if (errno == ERANGE || valor < INT_MIN || valor > INT_MAX) {
            printf("Numero fuera del rango de int (%d a %d).\n", INT_MIN, INT_MAX);
            continue;
        }

        *salida = (int)valor;
        return 1;
    }
}

void leer_valores(int arr[], int n) {
    int i;
    char prompt[64];

    for (i = 0; i < n; i++) {
        snprintf(prompt, sizeof(prompt), "Ingresa por favor el termino %d: ", i + 1);
        if (!leer_entero_seguro(prompt, &arr[i])) {
            arr[i] = 0;
        }
    }
}

void copiar_valores(const int origen[], int destino[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

void reiniciar_contexto(ContextoSort *ctx) {
    copiar_valores(ctx->original, ctx->datos, TAM);
    ctx->i = 0;
    ctx->j = 0;
    ctx->activo_a = -1;
    ctx->activo_b = -1;
    ctx->terminado = 0;
    ctx->pausado = 0;
    ctx->tiempo_acumulado = 0.0f;
}

void intercambiar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int maximo_arreglo(const int arr[], int n) {
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return (max > 0) ? max : 1;
}

/* =========================================================================
   MODIFICAR ESTA FUNCION PARA IMPLEMENTAR NUEVAS LOGICAS DE ORDENAMIENTO
   - Lee y modifica: ctx->datos[0 .. n-1]
   - Usa ctx->i, ctx->j como indices/contadores persistentes entre pasos
   - Marca ctx->activo_a y ctx->activo_b con los indices a resaltar en rojo
     (usa -1 si no quieres resaltar ninguno en ese paso)
   - Pon ctx->terminado = 1 cuando el arreglo ya este ordenado
   ========================================================================= */
void ejecutar_paso_sort(ContextoSort *ctx, int n) {
    if (n <= 1) {
        ctx->terminado = 1;
        ctx->activo_a = -1;
        ctx->activo_b = -1;
        return;
    }

    if (ctx->i < n - 1) {
        if (ctx->j < n - 1 - ctx->i) {
            ctx->activo_a = ctx->j;
            ctx->activo_b = ctx->j + 1;

            if (ctx->datos[ctx->j] > ctx->datos[ctx->j + 1]) {
                intercambiar(&ctx->datos[ctx->j], &ctx->datos[ctx->j + 1]);
            }

            ctx->j++;
        } else {
            ctx->j = 0;
            ctx->i++;
        }
    } else {
        ctx->activo_a = -1;
        ctx->activo_b = -1;
        ctx->terminado = 1;
    }
}

void actualizar_animacion(ContextoSort *ctx, float dt, int n) {
    if (ctx->terminado || ctx->pausado) {
        return;
    }

    ctx->tiempo_acumulado += dt;
    if (ctx->tiempo_acumulado >= ctx->intervalo) {
        ctx->tiempo_acumulado = 0.0f;
        ejecutar_paso_sort(ctx, n);
    }
}

void renderizar(const ContextoSort *ctx, int n) {
    int i;
    int max_val = maximo_arreglo(ctx->datos, n);
    int margen_x = 60;
    int ancho_total = ANCHO_VENTANA - (2 * margen_x);
    int paso_x = ancho_total / n;
    int ancho_barra = (paso_x > 12) ? (paso_x - 12) : paso_x;
    int suelo_y = ALTO_VENTANA - 90;
    int alto_max = 320;

    DrawText("Algoritmo: Bubble Sort", 60, 25, 24, DARKBLUE);
    DrawText(TextFormat("Estado: %s | Paso: %.2fs | i=%d j=%d",
             ctx->terminado ? "ORDENADO" : (ctx->pausado ? "PAUSADO" : "CORRIENDO"),
             ctx->intervalo, ctx->i, ctx->j),
             60, 58, 18, DARKGRAY);

    for (i = 0; i < n; i++) {
        int val = ctx->datos[i];
        int alto = 0;
        Color color = SKYBLUE;

        if (val > 0) {
            alto = (val * alto_max) / max_val;
            if (alto < 10) {
                alto = 10;
            }
        }

        int x = margen_x + (i * paso_x) + ((paso_x - ancho_barra) / 2);
        int y = suelo_y - alto;

        if (ctx->terminado) {
            color = LIME;
        } else if (i == ctx->activo_a || i == ctx->activo_b) {
            color = RED;
        }

        DrawRectangle(x, y, ancho_barra, alto, color);
        DrawText(TextFormat("%d", val), x + (ancho_barra / 2) - 8, suelo_y + 10, 18, BLACK);
    }

    DrawText("[R] Reiniciar   [SPACE] Pausar/Continuar   [UP/DOWN] Velocidad",
             60, ALTO_VENTANA - 35, 16, DARKGRAY);
}
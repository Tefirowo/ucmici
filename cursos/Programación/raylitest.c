#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

void dibujar();
void elegirypintar(int tamX, int tamY);
void flood_fill(int *matriz, int *regiones, int tamX, int tamY, int x, int y, int valor_objetivo, int id_region, int *contador_celdas);

int main(void)
{
    int tamX, tamY, tamXtemp, tamYtemp;
    printf("Sistema de matriz de zonas contiguas.\n");
    printf("Ingresa un tamaño de matriz X (X,Y) -> MAX (20,20): ");
    scanf("%d", &tamXtemp);

    if (tamXtemp <= 20 && tamXtemp > 0){
        tamX = tamXtemp;
        printf("Valor X asignado como %d\n", tamX);
    }
    else {
        printf("NO PUEDE SER MAYOR A 20 O MENOR A 0, TONTITO\n");
        return 0;
    }
    
    printf("Ingresa un tamaño de matriz Y (%d,Y)  -> MAX (20,20): ", tamX);
    scanf("%d", &tamYtemp);

    if (tamYtemp <= 20 && tamYtemp > 0){
        tamY = tamYtemp;
        printf("Valor Y asignado como %d\n", tamY);
    }
    else {
        printf("NO PUEDE SER MAYOR A 20 O MENOR A 0, TONTITO\n");
        return 0;
    }
    printf("Tu matriz tendrá un tamaño de (%d, %d)\n", tamX, tamY);

    elegirypintar(tamX, tamY);

    return 0;
}

// Función recursiva para Flood Fill 
void flood_fill(int *matriz, int *regiones, int tamX, int tamY, int x, int y, int valor_objetivo, int id_region, int *contador_celdas) {
    if (x < 0 || x >= tamX || y < 0 || y >= tamY) return;
    if (matriz[y * tamX + x] != valor_objetivo) return; // Debe coincidir con el color objetivo (0 o 1)
    if (regiones[y * tamX + x] != 0) return; // Ya visitada

    regiones[y * tamX + x] = id_region;
    (*contador_celdas)++;

    // Visitar vecinos (arriba, abajo, izquierda, derecha)
    flood_fill(matriz, regiones, tamX, tamY, x + 1, y, valor_objetivo, id_region, contador_celdas);
    flood_fill(matriz, regiones, tamX, tamY, x - 1, y, valor_objetivo, id_region, contador_celdas);
    flood_fill(matriz, regiones, tamX, tamY, x, y + 1, valor_objetivo, id_region, contador_celdas);
    flood_fill(matriz, regiones, tamX, tamY, x, y - 1, valor_objetivo, id_region, contador_celdas);
}

void elegirypintar(int tamX, int tamY){
    InitWindow(1000, 1000, "Matriz Interactiva - Zonas Contiguas");
    SetTargetFPS(60);

    // Matriz de dibujo (0 = blanco, 1 = negro)
    int *matriz = (int *)calloc(tamX * tamY, sizeof(int));
    // Matriz de regiones (0 = sin región, ID > 0 = número de región contigua)
    int *regiones = (int *)calloc(tamX * tamY, sizeof(int));

    float anchoCelda = 1000.0f / tamX;
    float altoCelda = 1000.0f / tamY;

    int estado = 0;               // 0: Editando, 1: Animando cálculo, 2: Selección de regiones
    int modo_animado = 0;         // 1 si se presionó 'A' antes de ENTER
    int region_seleccionada = -1; // ID de la región seleccionada

    // Variables de control para el escaneo y animación frame por frame
    int scan_x = 0, scan_y = 0;
    int id_actual = 1;
    int tam_reg_actual = 0;
    int x_actual_flood = -1, y_actual_flood = -1, val_actual_flood = 0;

    while (!WindowShouldClose())
    {
        // ESTADO 0: EDITANDO
        if (estado == 0) {
            // Activar/desactivar modo animado con la tecla 'A'
            if (IsKeyPressed(KEY_A)) {
                modo_animado = !modo_animado;
                printf("Modo animado graficado: %s\n", modo_animado ? "ACTIVADO" : "DESACTIVADO");
            }

            // Pintar celdas con clic izquierdo
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();
                int x = mouse.x / anchoCelda;
                int y = mouse.y / altoCelda;

                if (x >= 0 && x < tamX && y >= 0 && y < tamY) {
                    matriz[y * tamX + x] = !matriz[y * tamX + x]; // Alterna 0 y 1
                }
            }

            // Presionar ENTER para iniciar cálculo
            if (IsKeyPressed(KEY_ENTER)) {
                for (int i = 0; i < tamX * tamY; i++) regiones[i] = 0;
                id_actual = 1;
                scan_x = 0;
                scan_y = 0;

                if (modo_animado) {
                    estado = 1; // Pasa a estado de animación gráfica
                } else {
                    // Cálculo instantáneo (recursivo tradicional)
                    for (int y = 0; y < tamY; y++) {
                        for (int x = 0; x < tamX; x++) {
                            if (regiones[y * tamX + x] == 0) {
                                int val = matriz[y * tamX + x];
                                int tam_reg = 0;
                                flood_fill(matriz, regiones, tamX, tamY, x, y, val, id_actual, &tam_reg);
                                
                                if (tam_reg < 2) {
                                    for (int i = 0; i < tamX * tamY; i++) {
                                        if (regiones[i] == id_actual) regiones[i] = 0;
                                    }
                                } else {
                                    id_actual++;
                                }
                            }
                        }
                    }
                    estado = 2; // Pasa directo a selección
                    printf("Procesamiento completo. Regiones válidas: %d\n", id_actual - 1);
                }
            }
        }
        // ESTADO 1: ANIMANDO EL CÁLCULO RECURSIVO GRÁFICO (Frame por frame)
        else if (estado == 1) {
            // Buscamos la siguiente celda sin asignar región
            if (scan_y < tamY) {
                if (regiones[scan_y * tamX + scan_x] == 0) {
                    int val = matriz[scan_y * tamX + scan_x];
                    tam_reg_actual = 0;
                    // Llamamos a la función recursiva para esta celda
                    flood_fill(matriz, regiones, tamX, tamY, scan_x, scan_y, val, id_actual, &tam_reg_actual);

                    if (tam_reg_actual < 2) {
                        // Si tiene menos de 2 casillas, se descarta
                        for (int i = 0; i < tamX * tamY; i++) {
                            if (regiones[i] == id_actual) regiones[i] = 0;
                        }
                    } else {
                        id_actual++;
                    }
                }

                // Avanzar al siguiente píxel en la matriz
                scan_x++;
                if (scan_x >= tamX) {
                    scan_x = 0;
                    scan_y++;
                }
            } else {
                // Fin de la animación
                estado = 2;
                printf("Animación de regiones completada. Total válidas: %d\n", id_actual - 1);
            }
        }
        // ESTADO 2: SELECCIÓN DE REGIONES
        else if (estado == 2) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();
                int x = mouse.x / anchoCelda;
                int y = mouse.y / altoCelda;

                if (x >= 0 && x < tamX && y >= 0 && y < tamY) {
                    region_seleccionada = regiones[y * tamX + x];
                    if (region_seleccionada == 0) {
                        printf("Clic en celda sin región contigua válida (tamaño < 2).\n");
                    } else {
                        printf("¡Región %d seleccionada!\n", region_seleccionada);
                    }
                }
            }

            // Reiniciar con 'R'
            if (IsKeyPressed(KEY_R)) {
                estado = 0;
                modo_animado = 0;
                region_seleccionada = -1;
                for (int i = 0; i < tamX * tamY; i++) {
                    matriz[i] = 0;
                    regiones[i] = 0;
                }
                printf("Reiniciando tablero...\n");
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Dibujar la matriz de celdas
            for (int y = 0; y < tamY; y++) {
                for (int x = 0; x < tamX; x++) {
                    Color col = WHITE;

                    if (estado == 0) {
                        col = (matriz[y * tamX + x] == 1) ? BLACK : WHITE;
                    } else {
                        int reg = regiones[y * tamX + x];
                        if (reg > 0 && reg == region_seleccionada) {
                            col = GREEN; // Pintar de verde la zona seleccionada
                        } else {
                            // Mostrar colores base según matriz original
                            col = (matriz[y * tamX + x] == 1) ? BLACK : WHITE;
                        }
                    }

                    DrawRectangle(x * anchoCelda, y * altoCelda, anchoCelda, altoCelda, col);
                    DrawRectangleLines(x * anchoCelda, y * altoCelda, anchoCelda, altoCelda, LIGHTGRAY);
                }
            }

            // Textos de guía en pantalla según el estado
            if (estado == 0) {
                DrawText(TextFormat("Click: Pintar | [A] Animado: %s | ENTER: Procesar", modo_animado ? "ON" : "OFF"), 10, 10, 20, DARKGRAY);
            } else if (estado == 1) {
                DrawText("Calculando regiones recursivamente de forma gráfica...", 10, 10, 20, RED);
            } else {
                DrawText("Click en zona: Seleccionar en VERDE | R: Reiniciar", 10, 10, 20, DARKGRAY);
            }
        EndDrawing();
    }

    free(matriz);
    free(regiones);
    CloseWindow();
}

void pintar_region(){
    
}
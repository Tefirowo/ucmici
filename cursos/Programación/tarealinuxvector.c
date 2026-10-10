#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define TAM 5

// Códigos ASCII / ANSI para Linux
#define ESC 27
#define ENTER 10
#define FLECHA_ARRIBA 65
#define FLECHA_ABAJO 66
#define FLECHA_DERECHA 67
#define FLECHA_IZQUIERDA 68

// Limpia la pantalla en Linux
void limpiarPantalla() {
    system("clear");
}

// Emulación de _getch() en tiempo real para Linux
int _getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Desactiva el modo canónico (lectura byte a byte) y el eco por pantalla
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    // Restaurar la configuración original de la terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Función para capturar las secuencias de escape de las flechas
int obtenerTecla() {
    int tecla = _getch();
    
    if (tecla == ESC) {
        // Las flechas en Linux envían la secuencia ESC -> '[' -> Letra (A, B, C, D)
        // Verificamos si hay caracteres adicionales en el buffer
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN] = 0;  // Lectura no bloqueante
        newt.c_cc[VTIME] = 1; // Timeout corto
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        int siguiente = getchar();
        if (siguiente == '[') {
            int flecha = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return flecha; // Retorna FLECHA_ARRIBA (65), FLECHA_ABAJO (66), etc.
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ESC; // Si no hay secuencia, realmente fue la tecla ESC
    }
    return tecla;
}
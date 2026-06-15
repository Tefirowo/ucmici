#include <stdio.h> 
#include <math.h> 

/* nombres de variables declaradas como constantes */ 
#define MAX_ESTUDIANTES 30 
#define APROBATORIO 6.0 
 
double calcular_media(const double calif[], int n); 
double calcular_varianza(const double calif[], int n, double media); 
double calcular_desviacion(double varianza); 
double encontrar_maximo(const double calif[], int n); 
double encontrar_minimo(const double calif[], int n); 
int contar_aprobados(const double calif[], int n); 

/* Sección principal de entrada al programa */ 
int main() 
{ 
    double calificaciones[MAX_ESTUDIANTES]; 
    int num_estudiantes; 
    double media, varianza, desviacion, max_calif, min_calif; 
    int aprobados; 
    int i; 

    printf("Ingrese el número de estudiantes (max %d): ", MAX_ESTUDIANTES); 
    scanf("%d", &num_estudiantes); 
    if (num_estudiantes <= 0 || num_estudiantes > MAX_ESTUDIANTES) 
    { 
        printf("Número inválido.\n"); 
        return 1; 
    } 
    printf("Ingrese las calificaciones (0.0-7.0):\n"); 
    for (i = 0; i < num_estudiantes; i++) 
    { 
        printf("Estudiante %d: ", i + 1); 
        scanf("%lf", &calificaciones[i]); 
    } 
    /* Cálculos usando funciones */ 
    media = calcular_media(calificaciones, num_estudiantes); 
    varianza = calcular_varianza(calificaciones, num_estudiantes, media); 
    desviacion = calcular_desviacion(varianza); 
    max_calif = encontrar_maximo(calificaciones, num_estudiantes); 
    min_calif = encontrar_minimo(calificaciones, num_estudiantes); 
    aprobados = contar_aprobados(calificaciones, num_estudiantes); 
    /* Resultados */ 
    printf("\n=== RESULTADOS ===\n"); 
    printf("Media: %.2f\n", media); 
    printf("Varianza: %.2f\n", varianza); 
    printf("Desviación estándar: %.2f\n", desviacion); 
    printf("Calificación máxima: %.2f\n", max_calif); 
    printf("Calificación mínima: %.2f\n", min_calif); 
    printf("Estudiantes aprobados: %d de %d (%.1f%%)\n", 
           aprobados, num_estudiantes, (aprobados * 100.0) / num_estudiantes); 
    return 0; 
} 

/* de aquí en adelante las funciones */ 

double calcular_media(const double calif[], int n) {
    double suma = 0;
    int i;
    for (i = 0; i < n; i++) {
        suma += calif[i];
    }
    return suma / n;
}

 
double calcular_varianza(const double calif[], int n, double media) {
    double suma_cuadrados = 0;
    int i; 
    
    for (i = 0; i < n; i++) {
        suma_cuadrados += pow(calif[i] - media, 2);
    }
    return suma_cuadrados / n;
}

double calcular_desviacion(double varianza) {

    return sqrt(varianza);
}

double encontrar_maximo(const double calif[], int n) {
    double max = calif[0];
    int i; 
    
    for (i = 1; i < n; i++) {
        if (calif[i] > max) {
            max = calif[i];
        }
    }
    return max;
}

double encontrar_minimo(const double calif[], int n) {
    double min = calif[0];
    int i; 
    
    for (i = 1; i < n; i++) {
        if (calif[i] < min) {
            min = calif[i];
        }
    }
    return min;
}

int contar_aprobados(const double calif[], int n) {
    int contador = 0;
    int i; 
    
    for (i = 0; i < n; i++) {
        if (calif[i] >= APROBATORIO) {
            contador++;
        }
    }
    return contador;
}

/* fin de las funciones */
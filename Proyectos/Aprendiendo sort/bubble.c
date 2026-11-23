#include <stdio.h>

#define tam 10

int main(){

    printf("Con tamaño %d\n", tam);
    
    int num[tam];
    int i;
    for(i = 0; i < 10; i++){
        printf("Ingresa por favor el término %d: ", i+1);
        scanf("%d", &num[i]);
        printf("\n");
    }
    printf("Metiste estos valores:\n");

    for (i = 0; i < 10; i++){
        printf("%d\n", num[i]);

    }

    
    return 0;
}
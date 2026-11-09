#include <stdio.h>
#include <unistd.h>
int main(){

    char respuesta = 's';
    printf("Q wea, ahora tenemos menos de una semana para hacer esta wea? (s/n): ");
        scanf(" %c", &respuesta); 
    
    if (respuesta == 's' || respuesta == 'S'){
        printf("N");

        for (int i = 0; i < 93278; i++){
            printf("o");
            fflush(stdout);
            long delay = 50000 - (i * 200); 
            if (delay > 0) {
                usleep(delay); 
            }
        }
        printf("\n");
    }   
    else {
        printf("uf, que bueno\n");    
    }
    
    printf("Tu respuesta fue: %c\n", respuesta);

    return 0;
}

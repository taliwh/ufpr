#include <stdio.h>

int dividir(int, int, int*);

int main () {
    int resto;
    
    int resultado = dividir(-5, 2, &resto);

    printf("%d\n", resultado);
    printf("%d\n", resto);

    return 0;
}



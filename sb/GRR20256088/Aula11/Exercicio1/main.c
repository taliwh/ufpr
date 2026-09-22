#include <stdio.h>
#include "sumInts.h"

int main () {
    int valor1, valor2, resultado;

    scanf("%d %d", &valor1, &valor2);
    resultado = sumInts(valor1, valor2);
    printf("Resultado: %d\n", resultado);

    return 0;
}
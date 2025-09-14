/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

int main () {
    long min, n, max;

    srand (0); 
    scanf("%ld %ld", &n, &max); 
    min = -max;

    /* verifica se o numero lido esta fora do intervalo */
    if (n <= 0 || n >= 100 || max <= 0 || max >= 30)
        return 1;

    for (int i=1; i<=n; i++) {

        /* imprime cada iteracoes */
        printf("%d: ", i);

        /* imprime as duas fracoes sorteadas */
        struct racional r1 = sorteia_r(min, max);
        imprime_r(r1);
        printf(" ");
        struct racional r2 = sorteia_r(min, max);
        imprime_r(r2);
        printf(" ");

        /* avisa sobre situacoes invalidas */
        if (valido_r(r1) == 0 || valido_r(r2) == 0) { 
            printf("NUMERO INVALIDO\n");
            return 1;
        }

        /* verifica se a divisao eh invalida*/
        if (r2.num == 0) {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        /* impressao das operacoes */
        struct racional soma = soma_r(r1, r2);
        imprime_r(soma);
        printf(" "); 
        struct racional sub = subtrai_r(r1, r2);
        imprime_r(sub);
        printf(" ");
        struct racional mult = multiplica_r(r1,r2);
        imprime_r(mult);
        printf(" ");
        struct racional div = divide_r(r1,r2);
        imprime_r(div);
        printf("\n");
    }

    return (0);
}
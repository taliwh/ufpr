#include <stdio.h>
#include "fibo.h"

int main () {
    int n, val;
    printf("digite o n-esimo termo de fibonacci: ");
    scanf("%d", &n);
    val = fibo(n);
    if (val != -1)
        printf("o %d termo de fibonacci (comecando com 0) eh %d\n", n, val);
}

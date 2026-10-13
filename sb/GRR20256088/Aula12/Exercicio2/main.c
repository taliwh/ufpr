#include <stdio.h>

int fib (int n);

int main() {
    int n;

    scanf("%d", &n);

    n = fib(n);
    
    printf("%d\n", n);

    return 0;
}

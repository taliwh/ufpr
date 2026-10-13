#include <stdio.h>

int fat(int n);

int main() {
    int n;

    scanf("%d", &n);

    n = fat(n);

    printf("%d\n", n);    
    
    return 0;
}


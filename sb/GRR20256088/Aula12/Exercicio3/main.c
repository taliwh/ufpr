#include <stdio.h>

int digito(int k, int n);


int main() {
    int n, k;

    scanf("%d%d", &n, &k);

    printf("%d", digito(n, k));

    return 0;
}
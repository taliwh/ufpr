


#include <stdio.h>
#include <stdlib.h>

void ascii(int val, char *p) {
    if val
    *p = val % 10;
    ascii(val/10, p + 1);


}

int main() { 
    char *p;
    int val;

    scanf("%d", &val);

    ascii(val, p);
    
    printf("%s\n", p);

    free(p);
    return 0;
}
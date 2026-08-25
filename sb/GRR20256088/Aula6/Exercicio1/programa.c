#include <unistd.h>

int main(void) {
    char* strOla = "Ola\n";
    while (*strOla != '\0') {
        write(STDOUT_FILENO, strOla, 1);
        strOla++;
    }
    return 0;
}
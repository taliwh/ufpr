// programa principal do projeto "The Boys - 2024/2"
// Autor: Thalísia Arianna Fernandes Fleck, GRR 20256088

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "fprio.h"
#include "conjunto.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main () {
    // iniciar o mundo

    struct fila_t *fila;
    struct fprio_t *filaprio;

    struct item {
        int id;
        int valor;
    };
    struct item x1 = { .id = 1, .valor = 10 };
    struct item x2 = { .id = 2, .valor = 20 };
    struct item x3 = { .id = 4, .valor = 50 };
    struct item x4 = { .id = 6, .valor = 70 };
    
    fila = fila_cria();
    filaprio = fprio_cria();

    for (int i=0; i < 10; i++) {
        fila_insere(fila, i);
    }
    fila_imprime(fila);

    fprio_insere(filaprio, &x1, 1, 2);
    fprio_insere(filaprio, &x2, 0, 5);
    fprio_insere(filaprio, &x3, 3, 1);
    fprio_insere(filaprio, &x4, 8, 3);

    fprio_imprime(filaprio);
    printf("\n");
    
    // executar o laço de simulação

    // executar o laço de simulação

    // destruir o mundo :o

    return 0;
}


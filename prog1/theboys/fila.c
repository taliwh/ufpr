#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria () {
    struct fila_t *fila;

    fila = malloc(sizeof(struct fila_t));
    if (!fila)
        return NULL;

    fila -> num = 0;
    fila -> prim = NULL;
    fila -> ult = NULL;

	return fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f) {
	struct fila_nodo_t *filaprox;

    if (!f)
        return NULL;

    while (f -> prim) { /* enquanto f -> prim for diferente de nulo */
        filaprox = f -> prim -> prox;
        free(f -> prim);
        f -> prim = filaprox;
    }

	free(f); 
    f = NULL;
    
	return NULL;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f) {
    if (!f)
        return -1;

    return f -> num;
}

int item_japertence(struct fila_t *f, int item) {
    struct fila_nodo_t *aux;

    if (!f || !fila_tamanho(f))
        return 0;

    aux = f -> prim;
    while (aux != NULL) {
        if (aux -> item == item)
            return 1;
        aux = aux -> prox;
    }

    return 0;
}

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item) {
    struct fila_nodo_t *novo;

    if (!f || item_japertence(f, item))
        return -1;

    novo = malloc(sizeof(struct fila_nodo_t));
    if (!novo)
        return -1;

    novo -> item = item;
    novo -> prox =  NULL;

    if (!fila_tamanho(f))   /* fila vazia */
        f -> prim = novo;
    else                  /* fila nao vazia*/
        f -> ult -> prox = novo;
   
    f -> ult = novo;

    f -> num++;

    return fila_tamanho(f);
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item) {
    struct fila_nodo_t *aux;

    if (!f || !item || !fila_tamanho(f))
        return 0;
    
    aux = f -> prim;
    f -> prim = f -> prim -> prox;
    *item = aux -> item;
    free(aux);

    if (!fila_tamanho(f)) /* fila ficou vazia */
        f -> ult = NULL;

    f -> num--;
    
    return 1;
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f) {
    struct fila_nodo_t *aux;

    if (!f || !fila_tamanho(f))
        return;
    aux = f -> prim;
    while (aux -> prox != NULL) {
        printf("%d ", aux -> item);
        aux = aux -> prox;
    }

    printf("%d", aux -> item);
}
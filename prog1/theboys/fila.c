#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// retorna fila vazia, se falhar retorna null
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

// destroi a fila desalocando sua memoria
struct fila_t *fila_destroi (struct fila_t *f) {
	struct fila_nodo_t *filaprox;

    if (!f)
        return NULL;

    while (f -> prim) { 
        filaprox = f -> prim -> prox;
        free(f -> prim);
        f -> prim = filaprox;
    }

	free(f); 
    f = NULL;
    
	return NULL;
}

// informa o tamanho da fila
int fila_tamanho (struct fila_t *f) {
    if (!f)
        return -1;

    return f -> num;
}

// verifica se o item ja esta contido na fila
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

// insere um item no final da fila respeitando a prioridade
int fila_insere (struct fila_t *f, int item) {
    struct fila_nodo_t *novo;

    if (!f || item_japertence(f, item))
        return 0;

    novo = malloc(sizeof(struct fila_nodo_t));
    if (!novo)
        return 0;

    novo -> item = item;
    novo -> prox =  NULL;

    if (!fila_tamanho(f))   
        f -> prim = novo;
    else               
        f -> ult -> prox = novo;
   
    f -> ult = novo;

    f -> num++;

    return fila_tamanho(f);
}

// retira o primeiro item da fila e o devolve no parametro item
int fila_retira (struct fila_t *f, int *item) {
    struct fila_nodo_t *aux;

    if (!f || !item || !fila_tamanho(f))
        return 0;
    
    aux = f -> prim;
    f -> prim = f -> prim -> prox;
    *item = aux -> item;
    free(aux);

    f -> num--;
    if (!fila_tamanho(f))
        f -> ult = NULL;
    
    return 1;
}

// imprime todo o conteudo da fila
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
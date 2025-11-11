#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// descreve um nodo da fila 
struct fila_nodo_t {
	void *item ;			// item associado ao nodo
	struct fila_nodo_t *prox;	// próximo nodo
};

// descreve uma fila 
struct fila_t {
	struct fila_nodo_t *prim ;	// primeiro nodo da fila
	struct fila_nodo_t *fim;	// último nodo da fila
	int num ;			// número de itens na fila
};

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria () {
    struct fila_t *fila;

    fila = malloc(sizeof(struct fila_t));
    if (!fila)
    	return NULL;

	fila -> num = 0;
	fila -> prim = NULL;
	fila -> fim = NULL;
	
	return fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f) {
	struct fila_nodo_t *filaprox;

	while (f -> prim) {
		filaprox = f -> prim -> prox;
		free(f -> prim -> item);
		free(f -> prim);
		f -> prim = filaprox;
    }
	free(f); //o free devolve o espaco e tb deixa o ponteiro da fila nulo

	return NULL;
}

// Insere o item na fila
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fila_insere (struct fila_t *f, void *item);

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fila_retira (struct fila_t *f) {
	
}


// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f) {
    if (!f)
        return -1;

    return f -> num;
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f);

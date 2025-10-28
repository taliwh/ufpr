// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

#include "fprio.h"
#include <stdlib.h>
#include <stdio.h>

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{   
    void *item ;          // item associado ao nodo
    int   tipo ;          // tipo do item
    int   prio ;          // prioridade do item
    struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
    struct fpnodo_t *prim ;   // primeiro nodo da fila
    int num ;         // número de itens na fila
};
QUINTILIANOOOOOOOOOOOOOOOO
// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria () {
    struct fprio_t *fila;

    fila = malloc(sizeof(struct fprio_t));
    if (!(fila))
        return NULL;
    fila -> num = 0;
    fila -> prim = NULL;

    return fila;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f) {
    struct fpnodo_t *iterador;
    int qtd;

    if (!f)
        return -1;

    iterador = f -> prim;
    qtd = 0;
    while (iterador != NULL) {
        qtd++;
        iterador = iterador -> prox;
    }

    return qtd;
}

/*
// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f);
*/

/*
 *
 * 
*/
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {
    struct fpnodo_t *novo;
    struct fpnodo_t *aux;
    struct fpnodo_t *aux_ant;

    novo = malloc(sizeof(struct fpnodo_t));
    if (!(novo))
        return -1;
    novo -> item = item;
    novo -> prio = prio;
    novo -> tipo = tipo;

    if (!(fprio_tamanho(f))) {
        f -> prim = novo;
        novo -> prox = NULL;
        return 1;
    }

    if (fprio_tamanho(f) == 1) {
        f -> prim -> prox = novo;
        novo -> prox = NULL;
        return fprio_tamanho(f);
    }

    aux = f -> prim;
    while (aux -> prio <= prio && aux -> prox != NULL) {
        aux_ant = aux;
        aux = aux -> prox;
    }

    if (aux -> prio <= prio) { //inserir no ultimo baguio
        aux -> prox = novo;
        novo -> prox = NULL;
        return fprio_tamanho(f);
    }

    novo -> prox = aux;
    aux_ant -> prox = novo;
    return fprio_tamanho(f);
}

/*
// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio);
*/



// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f) {
    struct fpnodo_t *iterador;

    if (fprio_tamanho(f) == 0 || fprio_tamanho(f) == -1)
        return;
    iterador = f -> prim;
    while (iterador -> prox != NULL) {
        printf("(%d %d) ", iterador -> tipo, iterador -> prio);
        iterador = iterador -> prox;
    }
    printf("(%d %d)", iterador -> tipo, iterador -> prio);
}

// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

#include <stdlib.h>
#include <stdio.h>
#include "fprio.h"

// cria uma fila vazia e inicializa seus campos
// retorna ponteiro para a fila ou NULL se der erro
struct fprio_t *fprio_cria () {
    struct fprio_t *fila;

    fila = malloc(sizeof(struct fprio_t));
    if (!fila)
        return NULL;

    fila -> num = 0;
    fila -> prim = NULL;
    fila -> fim = NULL;
    
    return fila;
}

// retorna o numero de itens na fila
// caso a fila seja invalida, retorna -1
int fprio_tamanho (struct fprio_t *f) {
    if (!f)
        return -1;
    return f -> num;
}

// libera de forma segura toda a memoria usada pela fila, com 2 variaveis auxiliares percorrendo a fila
// retorna NULL no final
struct fprio_t *fprio_destroi (struct fprio_t *f) {
    struct fpnodo_t *aux, *aux_prox;

    aux = f -> prim;

    while (aux != NULL) {
        aux_prox = aux -> prox;
        free(aux -> item);
        free(aux);
        aux = aux_prox;
    }
    free(f);
    f = NULL;

    return NULL;
}

// verifica se ja existe um item com o mesmo tipo e prioridade na fila
// retorna 1 se ja existir ou 0 se nao
int fprio_japertence (struct fprio_t *f, void *item) {
    struct fpnodo_t *aux;

    if (!(fprio_tamanho(f)) || fprio_tamanho(f) == -1)
        return 0;

    aux = f -> prim;
    while (aux != NULL) {
        if (aux -> item == item)
            return 1;
        aux = aux -> prox;
    }

    return 0;
}
    

// insere um novo item na fila respeitando a ordem de prioridade
// antes de inserir, verifica se este já foi inserido antes com a função fprio_japertence
// percorre a fila com as variaveis auxiliares e, dependendo da condicao, o item pode ser inserido no inicio, meio ou fim
// retorna -1 em casos de erro ou o tamanho da lista caso contrario
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {
    struct fpnodo_t *novo, *aux, *aux_ant;

    if (!f || !item) 
        return -1; 

    novo = malloc(sizeof(struct fpnodo_t));
    if (!novo)
        return -1;

    novo -> item = item;
    novo -> prio = prio;
    novo -> tipo = tipo;

    aux_ant = NULL;
    aux = f -> prim;

    while (aux != NULL && aux -> prio <= prio) { 
        aux_ant = aux;
        aux = aux -> prox;
    }

    if (!aux_ant) {  // insere no comeco 
        novo -> prox = f -> prim;
        f -> prim = novo;
        f -> num++;
        return fprio_tamanho(f);
    }

    novo -> prox = aux; // insere no meio ou no fim 
    aux_ant -> prox = novo;
    f -> num++; 

    return fprio_tamanho(f);
}

// retira o primeiro item da fila e retorna ele
// tipo e prioridade sao retornados pelos parametros
// retorna NULL se a fila estiver vazia ou invalida
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {
    struct fpnodo_t *aux;
    void *item;

    if (!fprio_tamanho(f)|| !f|| !tipo || !prio)
        return NULL;

    aux = f -> prim;
    f -> prim = f -> prim -> prox;

    item = aux -> item;
    *tipo = aux -> tipo;
    *prio = aux -> prio;

    f -> num--;
    free(aux);

    return item;

}

// imprime o conteudo da fila no formato (tipo, prio)
// nao imprime nada se a fila estiver vazia ou invalida
void fprio_imprime (struct fprio_t *f) {
    struct fpnodo_t *aux;

    if (!fprio_tamanho(f)|| !f)
        return;

    aux = f -> prim;
    while (aux -> prox != NULL) {
        printf("(%d %d) ", aux -> tipo, aux -> prio);
        aux = aux -> prox;
    }
    
    printf("(%d %d)", aux -> tipo, aux -> prio);
}

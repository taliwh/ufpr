#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; // ponteiro para algum nodo da lista (iterador) 
    int tamanho;
};
/* ---------------------------------------------------------------------- */

// cria uma lista inicial alocada de tamanho nulo 
struct lista *lista_cria (){
    struct lista *lista;

    lista = malloc(sizeof(struct lista));

    if (!(lista))
        return NULL;
    
    lista -> ini = NULL;
    lista -> ptr = NULL;
    lista -> tamanho = 0; 

    return lista;
}

// desaloca todas as memorias e os ponteiros correspondentes recebem NULL;
// com a variavel aux, percorre toda a lista;
// utiliza-se a variavel aux_prox para nao haver perca de elementos da lista.
void lista_destroi (struct lista **lista){
    struct nodo *aux;
    struct nodo *aux_prox;

    aux = (*lista) -> ini;

    while (aux != NULL) {
        aux_prox = aux -> prox;
        free(aux);
        aux = aux_prox;
    }

    free(*lista);
    *lista = NULL;
}


// insere um novo nodo alocado com a chave escolhida no começo da lista 
int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *novo;

    novo = malloc(sizeof(struct nodo));

    if (!(novo))
        return 0;  

    novo -> chave = chave;
    novo -> prox = lista -> ini;
    lista -> ini = novo;
    lista -> tamanho++;

    return 1;
}

// insere um novo nodo alocado no final da lista;
// se a lista for vazia, é preferível inserir a chave com a função insere_inicio, pois não terá elementos antecessores;
// insere sem perca de elementos da lista, e atualiza o seu tamanho.
int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *novo;
    struct nodo *aux;


    if (lista_vazia(lista)) 
        return lista_insere_inicio(lista, chave);

    novo = malloc(sizeof(struct nodo));

    if (!(novo))
        return 0;   
    
    aux = lista -> ini;

    while (aux -> prox != NULL) 
        aux = aux -> prox;
    
    novo -> chave = chave;
    novo -> prox = NULL;
    aux -> prox = novo;
    lista -> tamanho++;

    return 1;
}


// insere um nodo com a chave escolhida de forma ordenada na lista;
// o nodo é inserido de forma com que não haja perca de elementos da lista;
// percorre os elementos da lista com variaveis auxiliares;
// se a lista for vazia ou se o primeiro elemento for maior que a chave, o nodo eh inserido no inicio;
// se achar algum elemento maior que a chave, basta inserir o nodo na posicao anterior do elemento;
// se nao achar nenhum valor, entao a chave ja eh o maior elemento, portanto, inserimos no final.
int lista_insere_ordenado (struct lista *lista, int chave){
    struct nodo *aux;
    struct nodo *ultimo;
    struct nodo *novo;

    if (lista_vazia(lista) || lista -> ini -> chave >= chave)
        return lista_insere_inicio(lista, chave);

    ultimo = lista -> ini;

    while (ultimo -> prox != NULL)
        ultimo = ultimo -> prox;

    if (ultimo -> chave < chave)
        return lista_insere_fim(lista, chave);

    novo = malloc(sizeof(struct nodo));

    if (!(novo))
        return 0;

    novo -> chave = chave;
    aux = lista -> ini;

    while (aux -> prox -> chave < chave) 
        aux = aux -> prox;

    novo -> prox = aux -> prox;
    aux -> prox = novo;
    lista -> tamanho++;

    return 1;
}

// indica se a lista está sem elementos 
int lista_vazia (struct lista *lista){
    if (!(lista -> ini))
        return 1;

    return 0;
}
 
// remove o primeiro elemento e indica a chave que foi retirada;
// verifica se a lista esta vazia;
// o ultimo elemento recebe free e o tamanho da lista eh atualizado.
int lista_remove_inicio (struct lista *lista, int *chave){
    struct nodo *aux;

    if (lista_vazia(lista))
        return 0;

    aux = lista -> ini;
    lista -> ini = lista -> ini -> prox;
    *chave = aux -> chave;
    free(aux);
    lista -> tamanho--;

    return 1;
}

// remove o último elemento e indica a chave que foi retirada;
// verifica se a lista esta vazia;
// se tem tamanho 1, eh preferivel chamar a funcao remove_inicio, ja que o elemento a ser removido nao tera um antecessor;
// senao, o ultimo elemento recebe free e o tamanho da lista eh atualizado.
int lista_remove_fim (struct lista *lista, int *chave){
    struct nodo *aux;
    struct nodo *aux_ant;

    if (lista_vazia(lista))
        return 0;

    if (lista_tamanho(lista) == 1)
        return lista_remove_inicio(lista, chave);

    aux = lista -> ini;
    while (aux -> prox != NULL ) {
        aux_ant = aux;
        aux = aux -> prox;
    }

    *chave = aux -> chave;
    aux_ant -> prox = NULL;
    free(aux);
    lista -> tamanho--;

    return 1;
}


// remove o nodo que contem a chave passada;
// se for o primeiro elemento ou a lista tiver um unico elemento, chama remove_inicio para facilitar;
// senao, percorre ate achar a chave e liga o nodo anterior ao proximo, removendo o atual e atualizando o tamanho.
int lista_remove_ordenado (struct lista *lista, int chave){
    struct nodo *aux;
    struct nodo *aux_ant;

    if (lista_vazia(lista))
        return 0;
    
    if (lista_tamanho(lista) == 1 || lista -> ini -> chave == chave)
        return lista_remove_inicio(lista, &chave);

    aux = lista -> ini;
    while (aux -> chave != chave) {
        aux_ant = aux;
        aux = aux -> prox;
    }

    aux_ant -> prox = aux -> prox;
    free(aux);
    lista -> tamanho--;

    return 1;
}

// retorna quantidade de elementos da lista 
int lista_tamanho (struct lista *lista){
    return lista -> tamanho;
}

// verifica se o elemento com tal chave pertence a lista 
int lista_pertence (struct lista *lista, int chave){
    struct nodo *aux;
    int pertence;

    pertence = 0;

    if (lista_vazia(lista))
        return 0;   

    aux = lista -> ini;
    while (aux != NULL) {
        if (aux -> chave == chave)
            pertence = 1;
        aux = aux -> prox;
    }

    if (pertence) 
        return 1;

    return 0;
}

// inicia o iterador 
void lista_inicia_iterador (struct lista *lista){
    lista -> ptr = lista -> ini;
}

// move a posicao do iterador e declara qual chave está sendo apontada 
int lista_incrementa_iterador (struct lista *lista, int *chave){
    if (!(lista -> ptr)) 
        return 0;

    *chave = lista -> ptr -> chave;
    lista -> ptr = lista -> ptr -> prox;

    return 1;
}
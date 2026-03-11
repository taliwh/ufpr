#include <stdio.h>
#include <stdlib.h>
#define qtd_maq 10

struct lista {
    int tam;
    struct maquina *sent;
}

struct maquina {
    int id;
    int prob; 
    struct maquina *ant;
    struct maquina *prox;
}
    
struct maquina *cria_maq(int id) {
    struct maquina *maq = malloc(sizeof(struct maquina));
    if (!maq)
        return NULL;

    maq -> id = id;
    maq -> prob = rand() % 101;
    maq -> ant = NULL;
    maq -> prox = NULL;

    return maq;
}

struct lista cria_lista() {
    struct lista *li = malloc(sizeof(struct lista));
    struct maquina *sent = malloc(sizeof(struct maquina));

    if (!li || !sent)
        return NULL; iug

    li -> tam = 0;
    li -> sent = sent;
    sent -> prox = sent;
    sent -> ant = sent;

    return li;
}

void insere_comeco (struct lista *li, struct maquina *maq) {
    if (!li || !maq)
        return NULL;

    li -> tam++;
    li -> sent = maq;

    maq -> prox = NULL;

}

void insere_ordenado (struct lista *li, struct maquina *maq, int prob) {
    if (!li || !maq)
        return NULL;

    li -> tam++;

    struct maquina *aux; 

    aux = li -> sent;
    while (aux -> prox != NULL && aux -> prob <= prob) 
        aux = aux -> prox; 

    maq -> ant = aux -> ant;
    maq -> prox = aux;
    aux -> ant -> prox = maq;
    aux -> ant = maq;

}

void insere_fim (struct lista *li, struct maquina *maq) {

}

int main () {
    srand(0);

    struct lista li = cria_lista();
    int prob_ant;

    li -> sent = sent;
    sent -> prox = sent;
    sent -> ant = sent;

    for (i = 0; i < qtd_maq; i++) {
        struct maq = cria_maq(i + 1);
        insere_ordenado(li, maq, maq -> prob);
    }


    return 0;
}

// programa principal do projeto "The Boys - 2024/2"
// Autor: Thalísia Arianna Fernandes Fleck, GRR 20256088

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"

// seus #defines vão aqui
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)


W *cria_mundo () {
    W *mundo;

    mundo = malloc(sizeof(W));
    if (!mundo) {
        printf("erro ao alocar mundo");
        return NULL;
    }

    mundo -> hab = N_HABILIDADES;
    mundo -> compstv = N_COMPOSTOS_V;
    mundo -> qtd_H = N_HEROIS;
    mundo -> qtd_B = N_BASES;
    mundo -> qtd_M = N_MISSOES;

    mundo -> clk = 0;

    mundo -> local.x = 20000;
    mundo -> local.y = 20000;

    mundo -> vet_H = malloc(N_HEROIS * sizeof(struct heroi));
    mundo -> vet_B = malloc(N_BASES * sizeof(struct base));
    mundo -> vet_M = malloc(N_MISSOES * sizeof(struct missao));

    if (!mundo -> vet_H || !mundo -> vet_B || !mundo -> vet_M) {
        printf("erro alocando vetores do mundo\n");
        return NULL;
    }

    return mundo;
}


// programa principal
int main () {
    srand(0);

    // struct fprio_t *lef = fprio_cria();
    // W *mundo = cria_mundo ();
    
    // executar o laço de simulação

    // executar o laço de simulação

    // destruir o mundo :o

    return 0;
}


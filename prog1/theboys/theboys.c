// programa principal do projeto "The Boys - 2024/2"
// Autor: Thalísia Arianna Fernandes Fleck, GRR 20256088

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "entidades.h"
#include "eventos.h"

// seus #defines vão aqui
#include "define.h"
//violacao de tad mudar depois !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

    mundo -> clk = T_INICIO;

    mundo -> local.x = N_TAMANHO_MUNDO;
    mundo -> local.y = N_TAMANHO_MUNDO;
    mundo -> vet_H = malloc(N_HEROIS * sizeof(struct heroi));
    mundo -> vet_B = malloc(N_BASES * sizeof(struct base));
    mundo -> vet_M = malloc(N_MISSOES * sizeof(struct missao));

    if (!mundo -> vet_H || !mundo -> vet_B || !mundo -> vet_M) {
        printf("erro alocando vetores do mundo\n");
        return NULL;
    }

    return mundo;
}
//eh tudoviolacaodetads fazer em outroarquivo
void inicializacao (W *mundo, H ) {

    //inicializacao dos herois
    for (int i = 0; i < N_HEROIS; i++) {
        HEROI(mundo, i).id = i; 
        HEROI(mundo, i).xp = 0;
        PACIENCIA_H(mundo, i) = aleat(0, 100);
        VELOCIDADE_H(mundo, i) = aleat(50, 5000);
        HABILIDADES_H(mundo, i) = cjto_cria(aleat(1, 3), N_HABILIDADES);
    }

    //inicializacao das bases
    for (int i = 0; i < N_BASES; i++) {
        BASE(mundo, i).id = i; 
        LOCAL_X_B(mundo, i) = aleat(0, N_TAMANHO_MUNDO - 1);
        LOCAL_Y_B(mundo, i) = aleat(0, N_TAMANHO_MUNDO - 1);
        LOTACAO_B(mundo, i) = aleat(3, 10);
        PRESENCA_B(mundo, i) = cjto_cria(N_HEROIS);
        OCUPACAO_B(mundo, i) = 0;
        QTD_FILA_ESPERA_B(mundo, i) = 0; 
    }

    //inicializacao das missoes
    for (int i = 0; i < N_MISSOES; i++) {
        MISSAO(mundo, i).id = i;
        LOCAL_X_M(mundo, i) = aleat(0, N_TAMANHO_MUNDO - 1);
        LOCAL_Y_M(mundo, i) = aleat(0, N_TAMANHO_MUNDO - 1);
        HABILIDADES_M(mundo, i) = cjto_aleat(aleat (6, 10), N_HABILIDADES);
    }

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


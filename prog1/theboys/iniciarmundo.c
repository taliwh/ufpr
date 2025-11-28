#include "iniciarmundo.h"

W *cria_mundo () {
    W *mundo;

    mundo = malloc(sizeof(W));
    if (!mundo) {
        printf("erro ao alocar mundo");
        return NULL;
    }

    COMPOSTOS_W(mundo) = N_COMPOSTOS_V;
    QTD_HAB_W(mundo) = N_HABILIDADES;    
    QTD_H_W(mundo) = N_HEROIS;
    QTD_B_W(mundo) = N_BASES;
    QTD_M_W(mundo) = N_MISSOES;
    QTD_E_W(mundo) = ZERADO;
    QTD_MI_W(mundo) = ZERADO;
    QTD_MORTE_W(mundo) = ZERADO;
    TEMPO_ATUAL_W(mundo) = T_INICIO;
    LOCAL_X_W(mundo) = N_TAMANHO_MUNDO;
    LOCAL_Y_W(mundo) = N_TAMANHO_MUNDO;
    mundo -> vet_H = malloc(N_HEROIS * sizeof(struct heroi));
    mundo -> vet_B = malloc(N_BASES * sizeof(struct base));
    mundo -> vet_M = malloc(N_MISSOES * sizeof(struct missao));

    for (int b = 0; b < N_BASES; b++) {
        mundo->vet_B[b].espera   = malloc(sizeof(struct cjto_t));
        mundo->vet_B[b].presenca = malloc(sizeof(struct cjto_t));

        mundo->vet_B[b].espera->num   = ZERADO;
        mundo->vet_B[b].presenca->num = ZERADO;
    }

    if (!mundo -> vet_H || !mundo -> vet_B || !mundo -> vet_M) {
        printf("erro alocando vetores do mundo\n");
        return NULL;
    }

    return mundo;
}

void inicializacao (W *mundo) {

    //inicializacao dos herois
    for (int h = 0; h < QTD_H_W(mundo); h++) {
        ID_H(mundo, h) = h; 
        XP_H(mundo, h) = 0;
        PACIENCIA_H(mundo, h) = aleat(0, 100);
        VELOCIDADE_H(mundo, h) = aleat(50, 5000);
        HABILIDADES_H(mundo, h) = cjto_aleat(aleat(1, 3), N_HABILIDADES);
    }

    //inicializacao das bases
    for (int b = 0; b < QTD_B_W(mundo); b++) {
        ID_B(mundo, b) = b; 
        LOCAL_X_B(mundo, b) = aleat(0, N_TAMANHO_MUNDO - 1);
        LOCAL_Y_B(mundo, b) = aleat(0, N_TAMANHO_MUNDO - 1);
        LOTACAO_B(mundo, b) = aleat(3, 10);
        PRESENCA_B(mundo, b) = cjto_cria(N_HEROIS);
        OCUPACAO_B(mundo, b) = 0;
        QTD_FILA_ESPERA_B(mundo, b) = 0; 
    }

    //inicializacao das missoes
    for (int m = 0; m < QTD_M_W(mundo); m++) {
        ID_M(mundo, m) = m;
        LOCAL_X_M(mundo, m) = aleat(0, N_TAMANHO_MUNDO - 1);
        LOCAL_Y_M(mundo, m) = aleat(0, N_TAMANHO_MUNDO - 1);
        HABILIDADES_M(mundo, m) = cjto_aleat(aleat (6, 10), N_HABILIDADES);
    }
}

void destroi_mundo(W *mundo) {
    
    for (int h = 0; h < QTD_H_W(mundo); h++) {
        cjto_destroi(HABILIDADES_H(mundo, h));
    }
    
    for (int b = 0 ; b < QTD_B_W(mundo) ; b++) {
        cjto_destroi(PRESENCA_B(mundo, b));
        fila_destroi(FILA_ESPERA_B(mundo, b));
    }

    for (int m = 0 ; QTD_M_W(mundo); m++) {
        cjto_destroi(HABILIDADES_M(mundo, m));
    }
    free(mundo -> vet_B);
    free(mundo -> vet_B);
    free(mundo -> vet_M);       
    free(mundo);
}

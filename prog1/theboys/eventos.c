#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "eventos.h"
#include "fprio.h"
#include "fila.h"
#include "entidades.h"
#include "conjunto.h"

struct evento {
    int tipo;
    int base;
    int baseprox; // so usa com viaja 
    int heroi;
    int tempo;
    double distancia; //so usa com viaja e umas coisas ai
    int missao;
};

int aleat (int min, int max) {
    int aleat;

    aleat = min + rand () % (max - min + 1);

    return aleat;
}

//retorna -1 se erro
double distancia_bases(W *mundo, struct evento *ev) {
    int x1;
    int x2;
    int y1;
    int y2;
    double soma;
    double distancia;
    
    if (!mundo || !ev) {
        printf("falha ao calcular distancia");
        return -1;
    }

    x1 = LOCAL_X_B(mundo, ev -> base);
    x2 = LOCAL_X_B(mundo, ev -> baseprox);

    y1 = LOCAL_Y_B(mundo, ev -> base);
    y2 = LOCAL_Y_B(mundo, ev -> baseprox);

    soma = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    distancia = sqrt(soma);

    return distancia;
}

struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, double distancia, int missao) {
    struct evento *evento_novo;

    evento_novo = malloc(sizeof(struct evento));
    if (!mundo || !evento_novo) {
        printf("falha ao criar evento");
        return NULL;
    }

    evento_novo -> tipo = tipo;
    evento_novo -> heroi = heroi;
    evento_novo -> tempo = tempo;
    evento_novo -> base = base;
    evento_novo -> baseprox = baseprox;
    evento_novo -> missao = missao;
    evento_novo -> distancia = distancia;

    return evento_novo;
}

void printa_evento(W *mundo, struct evento *ev, int tempoaux) {

    if (!mundo || !ev) {
        printf("falha ao printar");   
        return;
    }

    switch (ev -> tipo) {
        case TIPO_CHEGA:
            printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            //printf("\n");
            break;
        case TIPO_CHEGA_DESISTE:
            printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            //printf("\n");
            break;
        case TIPO_ESPERA:
            printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", ev -> tempo, ev -> heroi, ev -> base, QTD_FILA_ESPERA_B(mundo, ev -> base));
            //printf("\n");
            break;
        case TIPO_DESISTE:
            printf("%6d: DESIST HEROI %2d BASE %d", ev -> tempo, ev -> heroi, ev -> base);
            //printf("\n");
            break;
        case TIPO_AVISA:
            printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [", ev -> tempo, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            fila_imprime(FILA_ESPERA_B(mundo, ev -> base));
            printf("]");
            //printf("\n");
            printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d", ev -> tempo, ev -> base, ev -> heroi);
            //printf("\n");
            break;
        case TIPO_ENTRA:
            printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base), ev -> tempo + tempoaux);
            //printf("\n");
            break;
        case TIPO_SAI:
            printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)", ev -> tempo, ev -> heroi, ev -> base, OCUPACAO_B(mundo, ev -> base), LOTACAO_B(mundo, ev -> base));
            //printf("\n");
            break;
        case TIPO_VIAJA:
            printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %f VEL %d CHEGA %d", ev -> tempo + tempoaux, ev -> heroi, ev -> base, ev -> baseprox, ev -> distancia, VELOCIDADE_H(mundo, ev -> heroi), ev -> tempo);
            //printf("\n");
            break;
        case TIPO_MORRE:
            printf("%6d: MORRE HEROI %2d MISSAO %d",  ev -> tempo, ev -> heroi, ev -> missao);
            //printf("\n");
            break;
        // case TIPO_MISSAO:
        //     printf("")

        // case TIPO_FIM:
 







    }
}

void eventos_iniciais (W *mundo, struct fprio_t *lef) {
    struct evento *chega;
    struct evento *missao;
    struct evento *fim;
    int tempo;

    if (!lef || !mundo) {
        printf("falha em realizar eventos iniciais");
        return;
    }

    // para cada heroi:
    for (int i = 0; i < N_HEROIS; i++) {
        BASEATUAL_H(mundo, i) = aleat(0, N_BASES -1);
        tempo = aleat(0, 4320);
        chega = cria_evento(mundo, TIPO_CHEGA, BASEATUAL_H(mundo, i), -1, i, tempo, -1, -1); 
        fprio_insere (lef, chega, TIPO_CHEGA, tempo);
    }

    // para cada missao m:
    for(int i = 0; i < N_MISSOES; i++) {
        tempo = aleat(0, T_FIM_DO_MUNDO);
        missao = cria_evento(mundo, TIPO_MISSAO, -1, -1, -1, tempo, -1, i); 
        fprio_insere(lef, missao, TIPO_MISSAO, tempo);
    }

    // agendamento do evento fim:
    fim = cria_evento(mundo, TIPO_FIM, -1, -1, -1, T_FIM_DO_MUNDO, -1, -1);
    fprio_insere(lef, fim, TIPO_FIM, tempo);
}

void funcao_evento_chega (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *espera;
    struct evento *desiste;
    int vai_esperar;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento chega");
        return;
    }

    BASEATUAL_H(mundo, ev -> heroi) = ev -> base;

    if (OCUPACAO_B (mundo, ev->base) < LOTACAO_B(mundo, ev -> base) && !fila_tamanho(FILA_ESPERA_B(mundo, ev -> base)))
        vai_esperar = 1;
    else {
        if (PACIENCIA_H(mundo, ev -> heroi) > (10 * fila_tamanho(FILA_ESPERA_B(mundo, ev -> base)))) 
            vai_esperar = 1;
        else
            vai_esperar = 0;
    }

    if (vai_esperar) {
        espera = cria_evento(mundo, TIPO_ESPERA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
        fprio_insere(lef, espera, TIPO_ESPERA, TEMPO_ATUAL_W(mundo));
    }   
    else {
        desiste = cria_evento(mundo, TIPO_DESISTE, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao); 
        fprio_insere(lef, desiste, TIPO_DESISTE, TEMPO_ATUAL_W(mundo));
        ev -> tipo = TIPO_CHEGA_DESISTE;
    }

    printa_evento(mundo, ev, 0);
}

void funcao_evento_espera (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento espera");
        return;
    }

    fila_insere(FILA_ESPERA_B(mundo, ev -> base), ev -> heroi);

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao); 
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void funcao_evento_desiste (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *viaja;
    int baseproxnova;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento desiste");
        return;
    }

    baseproxnova = aleat(0, N_BASES - 1);

    viaja = cria_evento(mundo, TIPO_VIAJA, ev -> base, baseproxnova, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, viaja, TIPO_VIAJA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void funcao_evento_avisa (W *mundo, struct fprio_t *lef, struct evento *ev) {
    int heroi;
    struct evento *entra;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento avisa");
        return;
    }

    while ((OCUPACAO_B(mundo, ev -> base)) < LOTACAO_B(mundo, ev -> base)) {
        fila_retira(FILA_ESPERA_B(mundo, ev -> base), &heroi);
        cjto_insere((PRESENCA_B(mundo, ev -> base)), heroi);
    }

    entra = cria_evento(mundo, TIPO_ENTRA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, entra, TIPO_ENTRA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void funcao_evento_entra (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *sai;
    int tpb;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento entra");
        return;
    }   

    tpb = 15 + PACIENCIA_H(mundo, ev -> heroi) * aleat(1, 20);

    sai = cria_evento(mundo, TIPO_SAI, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo) + tpb, ev -> distancia, ev -> missao);
    fprio_insere(lef, sai, TIPO_SAI, TEMPO_ATUAL_W(mundo));
  
    printa_evento(mundo, ev, tpb);

}

void funcao_evento_sai (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *viaja;
    struct evento *avisa;
    int baseproxnova;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento sai");
        return;
    }   

    baseproxnova = aleat(0, N_BASES - 1);
    cjto_retira((PRESENCA_B(mundo, ev -> base)), ev -> heroi);

    viaja = cria_evento(mundo, TIPO_VIAJA, ev -> base, baseproxnova, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, viaja, TIPO_VIAJA, TEMPO_ATUAL_W(mundo));

    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));

    printa_evento(mundo, ev, 0);
}

void funcao_evento_viaja (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *chega;
    double distancia;
    int duracao;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento viaja");
        return;
    }   

    distancia = distancia_bases(mundo, ev);
    ev -> distancia = distancia;
    duracao = distancia / VELOCIDADE_H(mundo, ev -> heroi);

    chega = cria_evento(mundo, TIPO_CHEGA, ev -> baseprox, -1, ev -> heroi, TEMPO_ATUAL_W(mundo) + duracao, ev -> distancia, ev -> missao);
    fprio_insere(lef, chega, TIPO_CHEGA, TEMPO_ATUAL_W(mundo));

    printa_evento (mundo, ev, duracao);
}

void funcao_evento_morre (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento morre");
        return;
    }   

    cjto_retira((PRESENCA_B(mundo, ev -> base)), ev -> heroi);
    STATUS_H(mundo, ev -> heroi) = 0;   
    avisa = cria_evento(mundo, TIPO_AVISA, ev -> base, ev -> baseprox, ev -> heroi, TEMPO_ATUAL_W(mundo), ev -> distancia, ev -> missao);
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));

    printa_evento (mundo, ev, 0);
}

void funcao_evento_missao (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento

    if (!mundo || !lef || !ev) {
        printf("falha na funcao evento morre");
        return;
    }   

}
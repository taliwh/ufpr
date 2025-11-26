#include <stdlib.h>
#include "eventos.h"
#include "fprio.h"
#include "entidades.h"
#include "lista.h"
#include "define.h"

struct evento {
    int tipo;
    int base;
    int heroi;
    int tempo;
};

struct evento_missao {
    int tipo;
    int tempo;  
    int missaoid; 
};

int aleat (int min, int max) {
    int aleat;

    aleat = min + rand () % (max - min + 1);

    return aleat;
}

struct evento *cria_evento (int tipo, int base, int heroi, int tempo) {
    struct evento *evento_novo;

    evento_novo = malloc(sizeof(struct evento));
    if (!evento_novo)
        return 0;

    evento_novo -> tipo = tipo;
    evento_novo -> heroi = heroi;
    evento_novo -> tempo = tempo;
    evento_novo -> base = base;

    return evento_novo;
}

struct evento_missao *cria_evento_missao (int tipo, int missao_id, int tempo) {
    struct evento_missao *evento_novo;

    evento_novo = malloc(sizeof(struct evento_missao));
    if (!evento_novo)
        return 0;

    evento_novo -> tipo = tipo;
    evento_novo -> tempo = tempo;
    evento_novo -> missaoid = missao_id;

    return evento_novo;
}

//void printa_eventos ()

void eventos_iniciais (struct fprio_t *lef, W *mundo) {
    struct evento *chega;
    struct evento_missao *eventomissao;
    int tempo;

    if (!lef || !mundo)
        return;

    // para cada heroi:
    for (int i = 0; i < N_HEROIS; i++) {
        BASEATUAL_H(mundo, i) = aleat(0, N_BASES -1);
        tempo = aleat(0, 4320);
        chega = cria_evento(TIPO_CHEGA, BASEATUAL_H(mundo, i), i, tempo); 
        fprio_insere (lef, chega, TIPO_CHEGA, tempo);
    }

    // para cada missao m:
    for(int i = 0; i < N_MISSOES; i++) {
        tempo = aleat(0, T_FIM_DO_MUNDO);
        eventomissao = cria_evento_missao(TIPO_MISSAO, ID_M(mundo, i), tempo); 
        fprio_insere(lef, eventomissao, TIPO_MISSAO, tempo);
    }

    // agendar evento fim

}

void funcao_evento_chega (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *espera;
    struct evento *desiste;
    int vai_esperar;

    if (!mundo || !ev)
        return;

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
        espera = cria_evento(TIPO_ESPERA, ID_B(mundo, ev -> base), ID_H(mundo, ev -> heroi), TEMPO_ATUAL_W(mundo));
        fprio_insere(lef, espera, TIPO_ESPERA, TEMPO_ATUAL_W(mundo));
    }
    else {
        desiste = cria_evento(TIPO_DESISTE, ID_B(mundo, ev -> base), ID_H(mundo, ev -> heroi), TEMPO_ATUAL_W(mundo));
        fprio_insere(lef, desiste, TIPO_DESISTE, TEMPO_ATUAL_W(mundo));
    }
}

void funcao_evento_espera (W *mundo, struct fprio_t *lef, struct evento *ev) {
    struct evento *avisa;

    if (!mundo || !ev)
        return;

    fila_insere(FILA_ESPERA_B(mundo, ev -> base), ID_H(mundo, ev -> heroi));

    avisa = cria_evento(TIPO_AVISA, ID_B(mundo, ev -> base), ID_H(mundo, ev -> heroi), TEMPO_ATUAL_W(mundo));
    fprio_insere(lef, avisa, TIPO_AVISA, TEMPO_ATUAL_W(mundo));
}


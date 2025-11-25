#include <stdlib.h>
#include "eventos.h"
#include "fprio.h"

#define tipo_chega 1
#define tipo_espera 2
#define tipo_desiste 3
#define tipo_avisa 4
#define tipo_entra 5
#define tipo_sai 6
#define tipo_viaja 7
#define tipo_morre 8
#define tipo_missao 9
#define tipo_fim 10

struct evento *cria_evento (int tipo, int base, int heroi, int tempo, int missao) {
    struct evento *evento_novo;

    evento_novo = malloc(sizeof(struct evento));
    if (!evento_novo)
        return 0;

    evento_novo -> tipo = tipo;
    evento_novo -> heroi = heroi;
    evento_novo -> tempo = tempo;
    evento_novo -> base = base;
    evento_novo -> missao = missao;

    return evento_novo;
}

void eventos_iniciais (struct W *mundo) {
    struct evento *chega;
    struct evento *missao;
    int tempo;

    // para cada heroi:
    for (int i = 0; i < N_HEROIS; i++) {
        W -> vet_h[i].baseatual = rand () % N_BASES;
        tempo = rand () % 4321;
        chega = cria_evento(tipo_chega, vet_h[i].baseatual, i, tempo, -1); // -1 significa q o eventoi chega nao tem haver com missao
        fprio_insere (lef, chega, chega -> tipo, chega -> tempo);
    }

    // para cada missao m:
    for(int i = 0; i < N_MISSOES; i++) {
        tempo = rand () % T_FIM_DO_MUNDO;
        W -> vet_m[i].id = i;
        missao = cria_evento(tipo_missao, -1, -1, tempo, i); //-1 significa que a missao nao ocorre em nenhuma base e nao tem haver com heroi tb
        fprio_insere(lef, missao, tipo_missao, missao -> tempo);
    }

}


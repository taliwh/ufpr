#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"

#define tipo_chega 1
#define tipo_espera 2
#define tipo_desiste 3
#define tipo_avisa 4
#define tipo_entra 5
#define tipo_sai 6
#define tipo_viaja
#define tipo_morre
#define tipo_missao
#define tipo_fim

struct evento *cria_evento (struct evento *e, int tipo, int base, int heroi, int tempo, int missao) {
    struct evento *evento_novo;

    evento_novo = malloc(sizeof(struct evento));
    if (!evento_novo)
        return 0;

    evento_novo -> base = base;
    evento_novo -> heroi = heroi;
    evento_novo -> tempo = tempo;
    evento_novo -> missao = missao;

    return evento_novo;
}

void eventos_iniciais () {
    struct evento *chega;
    struct evento *missao;
    int tempo;

    // para cada heroi:
    for (int i = 0; i < N_HEROIS; i++) {
        vet_h[i].baseatual = rand () % (N_BASES - 1);
        tempo = rand () % 4320;
        chega = cria_evento(vet_h[i].baseatual, i, tempo, -1);
        fprio_insere (lef, chega, 1, chega -> tempo);
    }

    //para cada missao m:
    for(int i = 0; i < N_MISSOES; i++) {
        tempo = rand () % T_FIM_DO_MUNDO;
        W -> vet_m[i].id = i;
        missao = cria_evento(-1 , i, tempo, i) //-1 significa que a missao nao ocorre em nenhuma base
        fprio_insere(lef, missao, 9, missao -> tempo);
    }

}

funcao evento etc
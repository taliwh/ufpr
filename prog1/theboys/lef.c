#include "lef.h"
#include "eventos.h"

void comecar_lef(W *mundo, struct fprio_t *lef) {
    struct evento *ev;
    int tipo_evento, prio_evento, fim;
    fim = 0;

    if (!mundo || !lef) {
        printf("erro: mundo ou lef nulos\n");
        return;
    }

    while(!fim && fprio_tamanho(lef)) {
        ev = fprio_retira(lef, &tipo_evento, &prio_evento);

        if (!ev) 
            break;
        
        mundo -> clk = prio_evento; 

        switch (tipo_evento) {
            case TIPO_CHEGA:
                evento_chega(mundo, lef, ev);
                break;

            case TIPO_ESPERA:
                evento_espera(mundo, lef, ev);
                break;

            case TIPO_DESISTE:
                evento_desiste(mundo, lef, ev);
                break;

            case TIPO_AVISA:
                evento_avisa(mundo, lef, ev);
                break;

            case TIPO_ENTRA:
                evento_entra(mundo, lef, ev);
                break;

            case TIPO_SAI:
                evento_sai(mundo, lef, ev);
                break;

            case TIPO_VIAJA:
                evento_viaja(mundo, lef, ev);
                break;

            case TIPO_MORRE:
                evento_morre(mundo, lef, ev);
                break;

            case TIPO_MISSAO:
                evento_missao(mundo, lef, ev);
                break;

            case TIPO_FIM:
                evento_fim(mundo, lef, ev);
                fim = 1;
                break;
        }
        free(ev);
        ev = NULL;
    }

    destroi_mundo(mundo);
}

#ifndef EVENTOS_H
#define EVENTOS_H

#include <stdio.h>
#include <math.h>
#include "entidades.h"
#include "fprio.h"
#include "define.h"
#include "funcoes.h"

struct evento {
    int tipo;
    int base;
    int baseprox; 
    int heroi;
    int tempo;
    int missao;
};

struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, int missao);
void printa_evento(W *mundo, struct evento *ev, int aux);
void eventos_iniciais (W *mundo, struct fprio_t *lef);
void evento_chega (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_espera(W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_desiste(W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_avisa (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_entra (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_sai (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_viaja (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_morre (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_missao (W *mundo, struct fprio_t *lef, struct evento *ev);
void evento_fim (W *mundo, struct fprio_t *lef, struct evento *ev);

#endif

#ifndef EVENTOS_H
#define EVENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entidades.h"
#include "fprio.h"
#include "define.h"

struct evento;

int aleat(int min, int max);
int distancia_bases(int x1, int x2, int y1, int y2);
struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, double distancia, int missao);
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

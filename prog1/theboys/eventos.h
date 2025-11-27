#ifndef EVENTOS_H
#define EVENTOS_H

#include "entidades.h"
#include "fprio.h"
#include "fila.h"

struct evento;

int aleat(int min, int max);
double distancia_bases(W *mundo, struct evento *ev);
struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, int duracao, int missao, int tempoaux);
void printa_evento(W *mundo, struct evento *ev);
void eventos_iniciais (W *mundo, struct fprio_t *lef);
void funcao_evento_chega (W *mundo, struct fprio_t *lef, struct evento *ev);
void funcao_evento_espera(W *mundo, struct fprio_t *lef, struct evento *ev);
void funcao_evento_desiste(W *mundo, struct fprio_t *lef, struct evento *ev);
void funcao_evento_avisa (W *mundo, struct fprio_t *lef, struct evento *ev);
void funcao_evento_entra (W *mundo, struct fprio_t *lef, struct evento *ev);
void funcao_evento_sai (W *mundo, struct fprio_t *lef, struct evento *ev);

#endif

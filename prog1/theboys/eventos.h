#ifndef EVENTOS_H
#define EVENTOS_H

#include "entidades.h"
#include "fprio.h"

struct evento;

struct evento_missao;

struct evento *cria_evento (int tipo, int base, int heroi, int tempo, int missao);

struct evento_missao *cria_evento_missao (int tipo, M missao, int tempo);

void eventos_iniciais (struct fprio_t *lef, W *mundo);

#endif

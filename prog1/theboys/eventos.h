#ifndef EVENTOS
#define EVENTOS

#include "entidades.h"
#include "fprio.h"

typedef struct evento {
    int tipo;
    int base;
    int heroi;
    int tempo;
    int missao;
} E;

struct evento *cria_evento (int tipo, int base, int heroi, int tempo, int missao);

void eventos_iniciais (struct fprio_t *lef, W *mundo);

#endif

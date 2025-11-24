#ifndef EVENTOS
#define EVENTOS

#include "entidades.h"

typedef struct evento {

    int tipo;
    int base;
    int heroi;
    int tempo;
    int missao;

} E;

struct evento *cria_evento (int base, int heroi, int tempo);
void eventos_inicias ()


#endif

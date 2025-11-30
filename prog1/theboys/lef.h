#ifndef LEF_H
#define LEF_H

#include <stdio.h>
#include <stdlib.h>
#include "eventos.h"
#include "conjunto.h"
#include "iniciarmundo.h"

// a simulacao comeca com essa funcao, retirando os eventos da lef
void comecar_lef(W *mundo, struct fprio_t *lef);

#endif
#ifndef INICIARMUNDO_H
#define INICIARMUNDO_H

#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "conjunto.h"
#include "define.h"
#include "eventos.h"

// cria a struct mundo responsavel por gerenciar a simulacao
W *cria_mundo ();

// inicializa as structs pra comecar a simulacao
void inicializacao (W *mundo);

// destroi o mundo, desalocando tudo
void destroi_mundo(W *mundo);

#endif
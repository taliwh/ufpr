#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdlib.h>
#include <math.h>
#include "entidades.h"
#include "define.h"

int aleat (int min, int max);
int distancia_bases(int x1, int x2, int y1, int y2);
struct distancia *intercala (struct distancia *vetor, int a, int meio, int b);
struct distancia *merge_sort(struct distancia *vetor, int ini, int fim);
void incrementa_xp(W *mundo, int idbase);
int acha_experiente(W *mundo, int idbase);
struct cjto_t *habilidades_base (W *mundo, int idbase);

#endif
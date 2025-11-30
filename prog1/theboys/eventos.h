#ifndef EVENTOS_H
#define EVENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entidades.h"
#include "fprio.h"
#include "define.h"

// struct opaca de eventos
struct evento;

// gera um numero aleatorio entre min e max (inclusive)
int aleat (int min, int max);

// calcula a distancia (hipotenusa) entre duas coordenadas
int distancia_bases(int x1, int x2, int y1, int y2);

// funcoes para ordenar vetores de distancia de forma recursiva utilizando quick sort
struct distancia *intercala (struct distancia *vetor, int a, int meio, int b);
struct distancia *merge_sort(struct distancia *vetor, int ini, int fim);

// incrementa o xp de todos os herois pertencentes na base
void incrementa_xp(W *mundo, int idbase);

// retorna o status da vida do heroi. 0 se esta morto e 1 se esta vivo
int status_vida(W *mundo, struct evento *ev);

// acha o heroi mais top (com mais experiencia) na base
int acha_experiente(W *mundo, int idbase);

// retorna um conjunto de habilidades de todos os herois presentes na base
struct cjto_t *habilidades_base (W *mundo, int idbase);

// cria uma struct de eventos alocada
struct evento *cria_evento (W *mundo, int tipo, int base, int baseprox, int heroi, int tempo, int missao);

// funcoes que imprimem os eventos
void printa_evento(W *mundo, struct evento *ev, int aux);
void printa_missao (W *mundo, struct evento *ev, struct cjto_t *hab, int cumprida);

// funcoes que implementam os eventos da simulacao
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

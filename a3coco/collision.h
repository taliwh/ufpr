#ifndef __COLLISION__
#define __COLLISION__
#include "cat.h"
#include "land.h"

// verifica se o gato esta no chao, se tiver, retorna coordenada do chao, se nao tiver, retorna -1
int floor_collision(cat *player, world *land);
void wall_collision(cat *player, world *land, int vale);
int hazard_collision(cat *player, world *land, int *instakill);
int collision(struct body a, struct body b);
#endif
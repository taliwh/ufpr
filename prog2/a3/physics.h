#ifndef __PHYSICS__
#define __PHYSICS__

#include "game.h"
#include "cat.h"

void apply_gravity(cat *player, world *land);
void apply_jump(struct game *catland);
int entity_collision (struct body a, struct body b);
void floor_collision(cat *player, world *land);
int hazard_collision(cat *player, world *land, int *instakill);
void wall_collision(cat *player, world *land);
int fish2_taken(cat *player, world *land);
int fish1_taken(cat *player, world *land);

#endif
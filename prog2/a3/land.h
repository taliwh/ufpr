#ifndef __LAND__
#define __LAND__

#include "creatures.h"
#define Y_FLOOR 320
#define LAND_WIDTH 4224

#define NUM_HAZARDS 5
#define NUM_SOLIDS 13

struct solid {
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
};

struct hazard {
    unsigned short x;
    unsigned short y;
    unsigned short width; //largura
    unsigned short height;
};

typedef struct {
    enemy *fox;
    enemy *bird;
    fish *fish1;
    fish *fish2;
    struct solid *solids;
    struct hazard *hazards;
} world;

world* create_land();
void destroy_land(world* land);
unsigned char collision(struct body a, struct body b);
//int floor_collision(cat *player, world *land);
//unsigned char hazard_collision(struct body a, struct hazard);
        

#endif
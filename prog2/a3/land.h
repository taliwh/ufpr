#ifndef __LAND__
#define __LAND__

#include "creatures.h"
#define Y_FLOOR 320
#define LAND_WIDTH 4224

#define NUM_HAZARDS 5
#define NUM_SOLIDS 12
#define NUM_SOLIDS_MOVE 1
#define SPEED_SOLID 6

struct solid {
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
};

struct solid_move {
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
    int vel_x;
    int start_x;
    int end_x;
};

struct hazard {
    unsigned short x;
    unsigned short y;
    unsigned short width; //largura
    unsigned short height;
};

typedef struct {
    enemy *fox1;
    enemy *fox2;
    enemy *bird;
    fish *fish1;
    fish *fish2;
    struct solid_move *move;
    struct solid *solids;
    struct hazard *hazards;
} world;

world* create_land();
struct solid create_solid(int x, int y, int width, int height);
struct solid_move create_moving_solid(int x, int y, int width, int height, int vel_x, int start_x, int end_x);
void update_land(world *land);
void destroy_land(world* land);


#endif
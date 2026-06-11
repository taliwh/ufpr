#include <stdio.h>
#include <stdlib.h>
#include "land.h"

world* create_land () {
        world *land = malloc(sizeof(world));
        if (!land)
                return NULL;
        
        land->fox1 = create_fox(1024 , 256, 2050);
        land->fox2 = create_fox(2304 , 256, 2500);
        land->bird = create_bird(1408, 50, 2304);
        
        land->fish1 = create_fish(1984, 120, 1);
        land->fish2 = create_fish(3130, 150, 2);

        land->solids = malloc(sizeof(struct solid) * NUM_SOLIDS);
        land->move = malloc(sizeof(struct solid_move) * NUM_SOLIDS_MOVE);
        land->hazards = malloc(sizeof(struct hazard) * NUM_HAZARDS);

        if (!land->solids || !land->move || !land->hazards) {
                free(land);
                return NULL;
        }

        //primeiro bloco de terra 
        land->solids[0] = create_solid(0, 320, 640, 192);

        //little ponte dps do primeiro bloco
        land->solids[1] = create_solid(640, 320, 64, 64);

        //chao da 1 lava
        land->solids[2] = create_solid(640, 512, 192, 64);

        //segundo bloco de terra q vai ate a lava (onde vai aparecer a raposa)
        land->solids[3] = create_solid(832, 320, 1280, 192);

        //chao da 2 lava
        land->solids[4] = create_solid(2112, 384, 192, 128);

        //terceiro bloco de terra depois da lava ate o buraco
        land->solids[5] = create_solid(2304, 320, 700, 192);

        //quarto bloco de terra antes do buraco de espinho q tem o peixe
        land->solids[6] = create_solid(3020, 384, 64, 128);

        //littles pontes do espinho
        land->solids[7] = create_solid(3084, 448, 64, 64);
        land->solids[8] = create_solid(3212, 384, 64, 64);

        //chao do espinho
        land->solids[9] = create_solid(3084, 512, 192, 64);

        //ultimo bloco de terra (q tem a bandeira)
        land->solids[10] = create_solid(3276, 320, 948, 192);

        //plataformas saudaveis so com grama sem perigo eba
        land->solids[11] = create_solid(1664, 220, 145, 35);

        land->move[0] = create_moving_solid(1920, 173, 145, 47, SPEED_SOLID, 1920, 2304);

        //1 lava
        land->hazards[0] = (struct hazard){640, 488, 192, 24};

        //1 espinho
        land->hazards[1] = (struct hazard){832, 296, 64, 24};

        //2 lava
        land->hazards[2] = (struct hazard){2112, 320, 192, 64};

        //plataforma com espinho
        land->hazards[3] = (struct hazard){2688, 192, 140, 88};

        //espinho do chao
        land->hazards[4] = (struct hazard){3084, 499, 192, 13};

        return land;
}

struct solid create_solid(int x, int y, int width, int height) {
    return (struct solid){x, y, width, height};
}

struct solid_move create_moving_solid(int x, int y, int width, int height, int vel_x, int start_x, int end_x) {
    return (struct solid_move){x, y, width, height, vel_x, start_x, end_x};
}

void update_land(world *land) {
    if (!land)
        return;

    for (int i = 0; i < NUM_SOLIDS_MOVE; i++) {
        struct solid_move *s = &land->move[i];

        s->x += s->vel_x;

        if (s->x >= s->end_x)
            s->vel_x = -abs(s->vel_x);
        if (s->x <= s->start_x)
            s->vel_x = abs(s->vel_x);
    }
}

void destroy_land (world* land) {
        if (!land)
                return;

        destroy_fox(land->fox1);
        destroy_fox(land->fox2);
        destroy_bird(land->bird);
        destroy_fish(land->fish1);
        destroy_fish(land->fish2);

        free(land->solids);
        free(land->hazards);

        free(land);
}
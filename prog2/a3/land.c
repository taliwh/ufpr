#include <stdio.h>
#include <stdlib.h>
#include "land.h"
#include "cat.h"

world* create_land () {
        world *land = malloc(sizeof(world));
        if (!land)
                return NULL;
        
        land->fox = create_fox(1792 , 256, 1024);
        land->bird = create_bird(2304, 32, 1408);
        
        land->fish1 = create_fish(1984, 120, 1, 0);
        land->fish2 = create_fish(3080, 400, 2, 0);

        land->solids = malloc(sizeof(struct solid) * NUM_SOLIDS);
        land->hazards = malloc(sizeof(struct hazard) * NUM_HAZARDS);

        if (!land->solids || !land->hazards) {
                free(land);
                return NULL;
        }

        //primeiro bloco de terra 
        land->solids[0] = (struct solid){0, 320, 640, 192};

        //little ponte dps do primeiro bloco
        land->solids[1] = (struct solid){640, 320, 64, 64};

        //chao da 1 lava
        land->solids[2] = (struct solid){640, 512, 192, 64};

        //segundo bloco de terra q vai ate a lava (onde vai aparecer a raposa)
        land->solids[3] = (struct solid){832, 320, 1280, 192};

        //chao da 2 lava
        land->solids[4] = (struct solid){2112, 384, 192, 128};

        //terceiro bloco de terra depois da lava ate o buraco
        land->solids[5] = (struct solid){2304, 320, 716, 192};

        //quarto bloco de terra antes do buraco de espinho q tem o peixe
        land->solids[6] = (struct solid){3020, 384, 64, 128};

        //littles pontes do espinho
        land->solids[7] = (struct solid){3084, 448, 64, 64};
        land->solids[8] = (struct solid){3212, 384, 64, 64};

        //ultimo bloco de terra (q tem a bandeira)
        land->solids[9] = (struct solid){3276, 320, 948, 192};

        //plataformas saudaveis so com grama sem perigo eba
        land->solids[10] = (struct solid){1664, 215, 145, 51};
        land->solids[11] = (struct solid){1920, 173, 145, 47};

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

void destroy_land (world* land) {
        if (!land)
                return;

        destroy_fox(land->fox);
        destroy_bird(land->bird);
        destroy_fish(land->fish1);
        destroy_fish(land->fish2);

        free(land->solids);
        free(land->hazards);

        free(land);
}

unsigned char entity_collision (struct body a, struct body b) {
    if (a.x + a.side/2 < b.x - b.side/2)
        return 0;

    if (a.x - a.side/2 > b.x + b.side/2)
        return 0;

    if (a.y + a.side/2 < b.y - b.side/2)
        return 0;

    if (a.y - a.side/2 > b.y + b.side/2)
        return 0;

    return 1;
}

/*
int floor_collision(cat *player, world *land)
{
    int foot = player->box.y + player->box.side/2;

    for (int i = 0; i < NUM_SOLIDS; i++) {
        struct solid s = land->solids[i];

        if (player->box.x >= s.x &&
            player->box.x <= s.x + s.width &&
            (foot == s.y || (player->box.y - SIDE_CAT/2) >= s.y))
        {
            return 1;
        }
    }

    return 0;
}


unsigned char hazard_collision(struct body a, struct hazard) {

}
*/

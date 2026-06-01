#include <stdio.h>
#include <stdlib.h>
#include "land.h"

world* create_land () {
        world *land = malloc(sizeof(world));
        if (!land)
                return NULL;
        
        land->fox = create_fox(, );
        land->bird = create_bird(, );
        
        land->fish1 = create_fish();
        land->fish2 = create_fish();

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
        land->solids[2] = (struct solid){640, 512, 192, 64}

        //segundo bloco de terra q vai ate a lava (onde vai aparecer a raposa)
        land->solids[3] = (struct solid){832, 320, 1280, 192};

        //chao da 2 lava
        land->solids[4] = (struct solid){2112, 384, 192, 128}

        //terceiro bloco de terra depois da lava ate o buraco
        land->solids[5] = (struct solid){2304, 320, 716, 192};

        //quarto bloco de terra antes do buraco de espinho q tem o peixe
        land->solids[6] = (struct solid){3020, 384, 64, 128};

        //littles pontes do espinho
        land->solids[7] = (struct solid){3084, 448, 64, 64}
        land->solids[8] = (struct solid){3212, 384, 64, 64}

        //ultimo bloco de terra (q tem a bandeira)
        land->solids[9] = (struct solid){3276, 320, 948, 192};

        //plataformas saudaveis so com grama sem perigo eba
        land->solids[10] = (struct solid){1664, 177, 145, 51};
        land->solids[11] = (struct solid){1920, 128, 145, 47};

        //1 lava
        land->hazards[0] = (struct solid){640, 488, 192, 24}

        //1 espinho
        land->hazards[1] = (struct solid){832, 296, 64, 24}

        //2 lava
        land->hazards[2] = (struct solid){2112, 320, }

     
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

unsigned char collision (struct body a, struct body b)
{
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
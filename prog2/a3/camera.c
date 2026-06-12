#include <stdlib.h>

#include "camera.h"
#include "game.h"
#include "land.h"

struct camera* create_camera() {
        struct camera *cam = malloc(sizeof(struct camera));
        if (!cam)
                return NULL;

        // posicao inicial da camera
        cam->x = 0;

        return cam;
}

void update_camera(struct camera *cam, float player_x) {
        if (!cam)
                return;

        // centraliza a camera levemente a esquerda do player (1/3 da tela)
        cam->x = player_x - X_SCREEN / 3;

        //condicoes para a camera nao ir alem do tamanho do mundo 
        if (cam->x < 0)
                cam->x = 0;

        if (cam->x > LAND_WIDTH - X_SCREEN)
                cam->x = LAND_WIDTH - X_SCREEN;
}

void destroy_camera(struct camera *cam) {
        free(cam);
}
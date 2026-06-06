#include <stdlib.h>

#include "camera.h"
#include "game.h"
#include "land.h"

struct camera* create_camera() {
    struct camera *cam = malloc(sizeof(struct camera));

    if (!cam)
        return NULL;

    cam->x = 0;

    return cam;
}

void update_camera(struct camera *cam, float player_x) {

   //fgaz com q o player fique no centro da tela mas eu posso muda tb
    cam->x = player_x - X_SCREEN / 3;

    //ifs pra camera nao ir alem do tamanho do mundo ou p tras
    if (cam->x < 0)
        cam->x = 0;

    if (cam->x > LAND_WIDTH - X_SCREEN)
        cam->x = LAND_WIDTH - X_SCREEN;
}

void destroy_camera(struct camera *cam) {
    free(cam);
}
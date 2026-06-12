#ifndef __CAMERA__
#define __CAMERA__

// struct que representa a posicao da camera
struct camera {
    float x;
};

// cria a camera que segue o player
struct camera* create_camera();

// atualiza a posicao da camera conforme posicao do player
void update_camera(struct camera *cam, float player_x);

// libera a alocacao de memoria da camera
void destroy_camera(struct camera *cam);

#endif
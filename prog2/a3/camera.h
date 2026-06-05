#ifndef __CAMERA__
#define __CAMERA__

struct camera {
    float x;
};

struct camera* create_camera();
void update_camera(struct camera *cam, float player_x);
void destroy_camera(struct camera *cam);

#endif
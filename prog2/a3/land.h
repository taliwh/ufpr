#define Y_FLOOR 192
#define LAND_WIDTH 4224


struct sprite_enemy {

        ALLEGRO_BITMAP **move;
        ALLEGRO_BITMAP **attack;
};

struct enemies {

}

struct solid
    ALLEGRO_BITMAP **images;

    int current;

    float x;

    float speed;
};

struct problem?
struct platform_map
{
    ALLEGRO_BITMAP *image;

    float x;

    float speed;
};

unsigned char collision_2D(struct body player, struct body cause_death);
create_camera
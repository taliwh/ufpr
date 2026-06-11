#ifndef __CREATURES__
#define __CREATURES__

#include <allegro5/allegro5.h>	

#define NUM_FISH 2
#define NUM_FOX 2

//side de cada entidade
#define SIDE 64 

//quantidade de sprites 
#define FOX_SPRITE 4
#define BIRD_SPRITE 6

#define FOX_SPEED 18
#define BIRD_SPEED 18

enum face {
        LOOK_RIGHT,
        LOOK_LEFT
};

struct body {
        //direcao q o personagem ta olhando
        unsigned char face;

        //centro da box
        int x;																																
	int y;	
};

typedef struct {
    struct body box;
    ALLEGRO_BITMAP **sprites;
    int end_x;
    int start_x; 
    int vel_x;
    int sprite_counter;
} enemy;

typedef struct {
    struct body box;
    ALLEGRO_BITMAP *sprite;
    int collected;
} fish;

fish* create_fish(int x, int y, char fish_type);
enemy* create_fox(int x, int y, int end);
enemy* create_bird(int x, int y, int end);
ALLEGRO_BITMAP** load_foxsprite ();
ALLEGRO_BITMAP** load_birdsprite();
void update_fox(enemy *fox);
void update_bird(enemy *bird);
void draw_fox (enemy *fox, int cam);
void draw_bird(enemy *bird, int cam);
void destroy_fox(enemy* fox);
void destroy_foxsprite(ALLEGRO_BITMAP **sprites);
void destroy_bird(enemy* bird);
void destroy_birdsprite(ALLEGRO_BITMAP **sprites);
void destroy_fish(fish *pexe);

#endif
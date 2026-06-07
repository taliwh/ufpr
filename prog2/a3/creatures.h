#ifndef __CREATURES__
#define __CREATURES__

#include <allegro5/allegro5.h>	

//side de cada entidade
#define SIDE_CAT 64 //50
#define SIDE_BIRD 35
#define SIDE_FOX 25
#define SIDE_FISH 18

//quantidade de sprites 
#define FOX_SPRITE 4
#define BIRD_SPRITE 6

enum face {
        LOOK_RIGHT,
        LOOK_LEFT
};

struct body {
        //direcao q o personagem ta olhando
        unsigned char face;
        int side;
        //centro da box
        int x;																																
	int y;	
};

typedef struct {
    struct body box;
    ALLEGRO_BITMAP **sprites;
    int end_x;
} enemy;

typedef struct {
    struct body box;
    ALLEGRO_BITMAP *sprite;
} fish;

fish* create_fish(int x, int y, char fish_type, char collected);
enemy* create_fox(int x, int y, int end);
enemy* create_bird(int x, int y, int end);
ALLEGRO_BITMAP** load_foxsprite ();
ALLEGRO_BITMAP** load_birdsprite();
void destroy_fox(enemy* fox);
void destroy_foxsprite(ALLEGRO_BITMAP **sprites);
void destroy_bird(enemy* bird);
void destroy_birdsprite(ALLEGRO_BITMAP **sprites);
void destroy_fish(fish *pexe);

#endif
#ifndef __ENTIDADES__
#define __ENTIDADES__

//side de cada entidade
#define SIDE 64

//quantidade de sprites 
#define FOX_SPRITE 4
#define BIRD_SPRITE 6

enum face {
        LOOK_RIGHT,
        LOOK_LEFT
};

struct body {
        unsigned char side; 
        unsigned char face;
        unsigned short x;																																
	unsigned short y;	
};

typedef struct {
    struct body box;
    ALLEGRO_BITMAP **sprites;
    unsigned short start_x;
    unsigned short end_x;
} enemy;

typedef struct {
    struct body box;
    ALLEGRO_BITMAP *sprite;
    unsigned char collected;
} fish;

fish* create_fish(unsigned char x, unsigned char y);
enemy* create_fox(unsigned short x, unsigned short y, unsigned short start, unsigned short end);
enemy* create_bird(unsigned short x, unsigned short y, unsigned short start, unsigned short end);
ALLEGRO_BITMAP** load_foxsprite ();
ALLEGRO_BITMAP** load_birdsprite();
void destroy_fox(enemy* fox);
void destroy_foxsprite(ALLEGRO_BITMAP **sprites);
void destroy_bird(enemy* bird);
void destroy_birdsprite(ALLEGRO_BITMAP **sprites);
void destroy_fish(fish *pexe);

#endif
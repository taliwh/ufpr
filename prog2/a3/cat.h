#ifndef __CAT__
#define __CAT__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "joystick.h"
#include "creatures.h"

#define CAT_STEP 10	

//quantidade de cada sprite
#define RUN_SPRITE 5
#define WALK_SPRITE 5
#define JUMP_SPRITE 6

#define MAX_HP 5

enum frames {
    NORMAL,
    WALK,
    DOWN,
    JUMP,
    SCARED,

    NUM_FRAMES
};

struct sprite_cat {
        ALLEGRO_BITMAP *normal;
        ALLEGRO_BITMAP *scared;
        ALLEGRO_BITMAP *crouch;
        ALLEGRO_BITMAP **run;
        ALLEGRO_BITMAP **jump;
        ALLEGRO_BITMAP **walk;
};

typedef struct {			
        struct body box;// caixinha em volta do personagem (o corpo dele);																																																																																								
	unsigned char hp; 																																														
	joystick *control;		
        struct camera *camera; //camera q segue o jogador
        struct sprite_cat *sprites; 
        enum frames frame;																																																												
} cat;																																			

cat* create_cat(enum face face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);	
struct sprite_cat* load_catsprite();
void step_cat(cat* player, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);		
void destroy_catsprite(struct sprite_cat* sprites);																																				
void destroy_cat(cat *element);																											

#endif		
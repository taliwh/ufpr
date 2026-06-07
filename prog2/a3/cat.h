#ifndef __CAT__
#define __CAT__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "joystick.h"
#include "creatures.h"
#include "land.h"

#define CAT_STEP 10	

//quantidade de cada sprite
#define RUN_SPRITE 5
#define WALK_SPRITE 6
#define JUMP_SPRITE 5

#define MAX_HP 5
#define GRAVITY 10

enum frames {
    NORMAL,
    WALK,
    RUN,
    DOWN,
    JUMP,
    SCARED
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
        unsigned char sprite_counter;																																																						
} cat;																																			

cat* create_cat(enum face face, int x, int y, int max_x, int max_y);	
struct sprite_cat* load_catsprite();
void step_cat(cat* player, int speed, unsigned char trajectory, int max_x, int max_y);		
void update_position(cat *player);
void destroy_catsprite(struct sprite_cat* sprites);																																				
void destroy_cat(cat *element);																											
void apply_gravity(cat *player);
int cat_chao (cat *player, world *land);

#endif		
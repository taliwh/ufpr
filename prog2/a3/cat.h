#ifndef __CAT__
#define __CAT__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "joystick.h"
#include "creatures.h"
#include "land.h"
#include "camera.h"

#define CAT_STEP 10	

//quantidade de cada sprite
#define RUN_SPRITE 5
#define WALK_SPRITE 6
#define JUMP_SPRITE 7

#define MAX_HP 5
#define GRAVITY 3.5
#define VELOCITY 30

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

struct timer {
        int damage_timer;
        int death_timer;
        int just_died;
        int took_damage;
        int took_fish;
};

typedef struct cat {			
        struct body box;// caixinha em volta do personagem (o corpo dele);																																																																																								
	int hp; 																																														
	joystick *control;		
        struct camera *camera; //camera q segue o jogador
        struct sprite_cat *sprites; 
        enum frames frame;
        unsigned char sprite_counter;	
        struct timer cooldown;
        float vel_y;		
        int old_y;	
        int chao;
} cat;																																			

cat* create_cat(enum face face, int x, int y, int max_x, int max_y);	
struct sprite_cat* load_catsprite();
void step_cat(cat* player, int speed, unsigned char trajectory, int max_x);		
int cat_win(cat *player);
void update_position(cat *player, world *land);
void update_frame(cat *player);
void update_hp(cat *player, world *land);

void destroy_catsprite(struct sprite_cat* sprites);																																				
void destroy_cat(cat *element);																											
int cat_alive (cat *player);

int cat_onground(cat *player);

#endif		
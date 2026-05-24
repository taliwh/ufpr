#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#ifndef __CAT__ 																																	
#define __CAT__																																																														//Quantidade de pixels que um quadrado se move por passo

#include "joystick.h"																																																															//Estrutura e procedimentos relacionados ao controle da arma (pistola) no jogo

#define CAT_STEP 10	
#define CAT_SIDE 64

enum frames {
    NORMAL,
    WALK,
    DOWN,
    JUMP,

    NUM_FRAMES
};

enum face {
        LOOK_RIGHT,
        LOOK_LEFT
}

struct body {
        unsigned char side; 
        unsigned char face;
        unsigned short x;																																
	unsigned short y;	
};

struct sprite_cat {
        ALLEGRO_BITMAP *normal;

        ALLEGRO_BITMAP **run;
        ALLEGRO_BITMAP **walk;
        ALLEGRO_BITMAP **crouch;
        ALLEGRO_BITMAP **jump;

        ALLEGRO_BITMAP **attack;
        ALLEGRO_BITMAP *scared;
};

typedef struct {			
        struct body box;// caixinha em volta do personagem (o corpo dele);																																																																																								
	unsigned char hp; 																																														
	joystick *control;		
        struct camera *camera; //camera q segue o jogador
        struct sprite_cat *sprites; 
        enum frames frame;																																																												
} cat;																																			

cat* create_cat(unsigned char side, enum face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);	
void step_cat(cat *player, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);						
void move_cat(cat *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);																																	
void destroy_cat(cat *element);																											

#endif		
#ifndef __CAT__
#define __CAT__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "joystick.h"
#include "creatures.h"
#include "land.h"
#include "camera.h"

// deslocamento do player
#define CAT_STEP 10	

// quantidade de sprites disponiveis para cada acao
#define RUN_SPRITE 5
#define WALK_SPRITE 6
#define JUMP_SPRITE 7

#define MAX_HP 5       // maximo de hp do player
#define VELOCITY 30    // velocidade do player

// frames que indicam o estado do personagem
enum frames {
    NORMAL,    // parado
    WALK,      // andando
    RUN,       // correndo
    DOWN,      // agachado
    JUMP       // pulando
};

// armazenamento de sprites
struct sprite_cat {
        ALLEGRO_BITMAP *normal;   // parado (1)
        ALLEGRO_BITMAP *crouch;   // agachado (1)
        ALLEGRO_BITMAP **run;     // vetor: correndo
        ALLEGRO_BITMAP **jump;    // vetor: pulando
        ALLEGRO_BITMAP **walk;    // vetor: andando
};

// timer
struct timer {
        int damage_timer; // controla a velocidade em que o player leva dano
        int death_timer;  // controla a velocidade em que o player morre
        int just_died;    // indica quando o player acabou de morrer
        int took_damage;  // indica quando o player acabou de levar dano
        int took_fish;    // indica quando o player acbaou de pegar algum coletável
};

// struct do player
typedef struct cat {			
        struct body box;                 // caixinha em volta do personagem (o corpo dele)																																																																																								
        struct camera *camera;           // camera que o segue
        struct sprite_cat *sprites;      // vetor de sprites
        enum frames frame;               // frame que indica o estado atual
        struct timer cooldown;           // cooldown e indicadores 
        joystick *control;		 // controle de movimento
        float vel_y;		         // velocidade vertical
        unsigned char sprite_counter;	 // indicacao do sprite atual
        unsigned char hp; 	                 // quantidade de hp																																													
        int old_y;	                 // 1 posicao anterior do jump
        unsigned char chao;                        // indica se o player esta no chao
} cat;																																			

// aloca e inicializa o player na posicao dada
cat* create_cat(enum face face, int x, int y, int max_x, int max_y);	

// carrega todos os sprites do gato
struct sprite_cat* load_catsprite();

// move o player horizontalmente na direcao indicada
void step_cat(cat* player, int speed, unsigned char trajectory, int max_x);		

// atualiza a posicao do gato sem que ele colida com alguma coisa
void update_position(cat *player, world *land);

// atualiza o frame do sprite com base no estado do joystickt
void update_frame(cat *player);

// atualiza o hp do player com base em colisoes com perigos e inimigos
void update_hp(cat *player, world *land);

// libera a alocacao de memoria dos sprites do gato
void destroy_catsprite(struct sprite_cat* sprites);	

// libera a alocacao de memoria dos sprites do player
void destroy_cat(cat *element);		

// retorna 1 se o player chegou ao fim do nivel
int cat_win(cat *player);	

// retorna 1 se o player se encontra no chao
int cat_onground(cat *player);		

// retorna 1 se o player esta vivo
int cat_alive (cat *player);



#endif		
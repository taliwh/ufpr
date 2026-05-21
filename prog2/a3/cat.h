#ifndef __CAT__ 																																	
#define __CAT__																																																														//Quantidade de pixels que um quadrado se move por passo

#include "joystick.h"																																																															//Estrutura e procedimentos relacionados ao controle da arma (pistola) no jogo

#define CAT_STEP 10																																

struct body {
        unsigned char apothem; // ""raio"" do quadrado (distancia do centro ate a borda) basicamente side / 2
        unsigned char face; //pra onde o gato ta olhando
        unsigned short x;																																
	unsigned short y;	
} 

typedef struct {			
        struct body square;// caixinha em volta do personagem;																																																																																								
	unsigned char hp; 																													
																													
	joystick *control;																																																																
} cat;																																			


//. Enumera frames do player
enum frames
{
    INACTIVE_1,
    RUN_1,
    RUN_2,
    RUN_3,
    RUN_4,
    FIRE_1,
    FIRE_2,
    FIRE_3,
    DOWN_1,
    JUMP_1,

    NUM_FRAMES
};


struct player
{
    short hp;                  // Vida
    unsigned char face;        // Direção em que está virado
    ALLEGRO_BITMAP **total_hp; // Imagens para representar a vida
    struct camera *camera;     // Câmera que segue o jogador
    struct hitbox *hitbox;     // Área de colisão
    struct joystick *control;  // Controle do jogador
    ALLEGRO_BITMAP **images;   // Vetor de imagens
    enum frames frame;         // Frame atual
};




cat* cat_create(unsigned char side, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);	
void cat_move(cat *element, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y);																																	
void cat_destroy(cat *element);																											

#endif		
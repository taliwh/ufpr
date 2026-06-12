#ifndef __CREATURES__
#define __CREATURES__

#include <allegro5/allegro5.h>	

// quantidade das entidades presentes no jogo
#define NUM_FISH 2
#define NUM_FOX 2

// lado da hitbox (side) de cada entidade
#define SIDE 64 

//quantidade de sprites 
#define FOX_SPRITE 4
#define BIRD_SPRITE 6

// velocidade das entidades
#define FOX_SPEED 18
#define BIRD_SPEED 18

// indicador da direcao do personagem
enum face {
        LOOK_RIGHT,
        LOOK_LEFT
};

// corpo da entidade 
struct body {
        int x;		           // centro x do personagem																													
	int y;	                   // centro y do personagem
        unsigned char face;        // direcao que o personagem ta olhando
};

// representacao de um inimigo
typedef struct {
        int start_x;               // comeco da sua trajetoria
        int end_x;                 // final da sua trajetoria
        int vel_x;                 // velocidade
        unsigned char sprite_counter;        // indicacao do sprite atual
        struct body box;           // hit box
        ALLEGRO_BITMAP **sprites;  // vetor de sprites
} enemy;

// representacao do coletavel
typedef struct {
        unsigned char collected;             // indicador se foi coletado
        struct body box;           // hit box
        ALLEGRO_BITMAP *sprite;    // sprite
} fish;

// cria o coletavel
fish* create_fish(int x, int y, char fish_type);

// cria o inimigo raposa
enemy* create_fox(int x, int y, int end);

// cria o inimigo ave
enemy* create_bird(int x, int y, int end);

// carrega os sprites dos inimigos
ALLEGRO_BITMAP** load_foxsprite ();
ALLEGRO_BITMAP** load_birdsprite();

// atualiza posicao dos inimigos
void update_fox(enemy *fox);
void update_bird(enemy *bird);

// renderiza os inimigos
void draw_fox (enemy *fox, int cam);
void draw_bird(enemy *bird, int cam);

// libera a alocacao de memoria dos inimigos e dos coletaveis
void destroy_fox(enemy* fox);
void destroy_foxsprite(ALLEGRO_BITMAP **sprites);
void destroy_bird(enemy* bird);
void destroy_birdsprite(ALLEGRO_BITMAP **sprites);
void destroy_fish(fish *pexe);

#endif
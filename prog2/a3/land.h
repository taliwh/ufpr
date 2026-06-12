#ifndef __LAND__
#define __LAND__

#include "creatures.h"

// coordenada y do chao principal
#define Y_FLOOR 320

// largura do mundo
#define LAND_WIDTH 4224

// numero de obstaculos e blocos
#define NUM_HAZARDS 5
#define NUM_SOLIDS 12
#define NUM_SOLIDS_MOVE 1

// velocidade da plataforma em movimento
#define SPEED_SOLID 6

// gravidade do mundo
#define GRAVITY 3.5    

// posicao da bandeira de win no jogo
#define BANDEIRA_X 3663

struct solid {
        unsigned short x;          // x inicial
        unsigned short y;          // y inicial
        unsigned short width;      // largura
        unsigned short height;     // altura
};

struct solid_move {
        unsigned short x;          // x inicial
        unsigned short y;          // y inicial
        unsigned short width;      // largura
        unsigned short height;     // altura
        int vel_x;                 // velocidade
        int start_x;               // comeco da trajetoria
        int end_x;                 // final da trajetoria
};

struct hazard {
        unsigned short x;           // x inicial
        unsigned short y;           // y inicial
        unsigned short width;       // largura
        unsigned short height;      // altura
};

// representacao do mundo do jogo e de suas entidades
typedef struct {
        enemy *fox1;                // raposa 1
        enemy *fox2;                // raposa 2
        enemy *bird;                // ave
        fish *fish1;                // peixe 1 (coletavel)
        fish *fish2;                // peixe 2 (coletavel)
        struct solid_move *move;    // vetor de blocos moveis
        struct solid *solids;       // vetor de blocos estaticos
        struct hazard *hazards;     // vetor de blocos que dao dano
} world;

// cria e posiciona todos os elementos do mundo: inimigos, peixes, plataformas e perigos
world* create_land();

// cria os blocos do jogo
struct solid create_solid(int x, int y, int width, int height);
struct solid_move create_moving_solid(int x, int y, int width, int height, int vel_x, int start_x, int end_x);

// atualiza a posicao da plataforma movel
void update_land(world *land);

// libera a alocacao de memoria do mundo
void destroy_land(world* land);

#endif
#ifndef __PHYSICS__
#define __PHYSICS__

#include "game.h"
#include "cat.h"

// verifica se o player colidiu com algum perigo do mundo
// define em *instakill se o dano deve matar na hora (lava/buraco) ou so tirar 1 hp (espinho)
int hazard_collision(cat *player, world *land, int *instakill);

// retorna 1 se duas entidades se colidirem
int entity_collision (struct body a, struct body b);

// coloca o player em cima do chao quando ele cai sobre uma superficie
// usa old_y para garantir que so detecta queda de cima para baixo
void floor_collision(cat *player, world *land);

// empurra o player para fora de paredes laterais
// so verifica colisao lateral quando a cabeca do player esta dentro da altura do solido
void wall_collision(cat *player, world *land);

// aplica gravidade: incrementa velocidade vertical e move o player para baixo
// salva a posicao anterior em old_y para o calculo de floor_collision
void apply_gravity(cat *player, world *land);

// aplica o pulo se o player estiver no chao
// com o segundo peixe coletado, permite pulo infinito no ar
void apply_jump(struct game *catland);

// retorna 1 e marca os peixes como coletados se o player alcanca-los
int fish2_taken(cat *player, world *land);
int fish1_taken(cat *player, world *land);

#endif
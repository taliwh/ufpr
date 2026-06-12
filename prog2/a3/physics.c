
#include "physics.h"
#include <stdio.h>

int hazard_collision(cat *player, world *land, int *instakill) {
        if (!player || !land)
                return -1;

        // bordas do personagem
        int left  = player->box.x - SIDE/2;
        int right = player->box.x + SIDE/2;
        int head  = player->box.y - SIDE/2;
        int foot = player->box.y + SIDE / 2;

        for (int i = 0; i < NUM_HAZARDS; i++) {
                struct hazard s = land->hazards[i];

                if (right > s.x && left < s.x + s.width &&
                foot > s.y && head < s.y + s.height) {

                        // se o player estiver agachado, ele passa pela plataforma de espinho (hazard 3)
                        if (i == 3 && player->control->crouch) 
                                return 0;

                        // hazards 0, 2 e 4 sao lavas e buracos: matam instantaneamente
                        if (i == 0 || i == 2 || i == 4)
                                *instakill = 1;

                        return 1;
                }
        }
        
        return 0;
}

int entity_collision (struct body a, struct body b) {
        if (a.x + SIDE/2 < b.x - SIDE/2)
                return 0;

        if (a.x - SIDE/2 > b.x + SIDE/2)
                return 0;

        if (a.y + SIDE/2 < b.y - SIDE/2)
                return 0;

        if (a.y - SIDE/2 > b.y + SIDE/2)
                return 0;

        return 1;
}

void floor_collision(cat *player, world *land) {
        if (!player || !land)
                return;

        int old_foot = player->old_y + SIDE / 2;
        int new_foot = player->box.y + SIDE / 2;

        // verifica colisao com chao de plataformas estaticas
        for (int i = 0; i < NUM_SOLIDS; i++) {
                struct solid s = land->solids[i];

                // zera a velocidade do jogador se ele estiver no chao, e atualiza sua posicao
                if (player->box.x >= s.x && 
                    player->box.x <= s.x + s.width && 
                    old_foot <= s.y && new_foot >= s.y) {
                        player->box.y = s.y - SIDE/ 2;
                        player->vel_y = 0; 
                        player->chao = 1; 
                    }
        }

        // verifica colisao com chao de plataformas moveis: arrasta o player junto na horizontal
        for (int i = 0; i < NUM_SOLIDS_MOVE; i++) {
                struct solid_move *s = &land->move[i];
                
                // mesmo if de antes, mas se o player esta no chao, ele eh arrastado junto com a plataforma
                if (player->box.x >= s->x &&
                    player->box.x <= s->x + s->width &&
                    old_foot <= s->y && new_foot >= s->y) {
                        player->box.y = s->y - SIDE / 2;
                        player->vel_y = 0;
                        player->chao = 1;
                        player->box.x += s->vel_x; 
                }
        }
}

void wall_collision(cat *player, world *land) {
        if (!player || !land)
                return;

        // bordas do personagem
        int left  = player->box.x - SIDE/2;
        int right = player->box.x + SIDE/2;
        int head  = player->box.y - SIDE/2;

        for (int i = 0; i < NUM_SOLIDS; i++) {
                struct solid s = land->solids[i];

                // verificacao se o player esta na altura da parede 
                if (head >= s.y && head < s.y + s.height) {

                        // parede a direita do player
                        if (s.x >= player->box.x && right >= s.x)
                                player->box.x = s.x - SIDE/2;
                        
                        // parede a esquerda do player
                        else if (player->box.x > s.x + s.width && left <= s.x + s.width)
                                player->box.x = s.x + s.width + SIDE/2;
                }
        }
}

void apply_gravity(cat *player, world *land) { 
        if (!player || !land)       
                return; 

        player->old_y = player->box.y; 
        player->vel_y += GRAVITY; 
        player->box.y += player->vel_y;

}

// se ele tive o coletavel pode pula quantas vezes quiser
void apply_jump(struct game *catland) {
        if (cat_alive(catland->player) && (catland->land->fish2->collected || cat_onground(catland->player))) {
                catland->player->vel_y = -VELOCITY;
                catland->player->chao = 0;
                joystick_jump_down(catland->player->control);
        }
}

int fish1_taken(cat *player, world *land) {
        if (!player || !land)
                return -1;


        if (!land->fish1->collected) {

                int right =player->box.x + SIDE/2;
                int foot = player->box.y + SIDE/2;
                int head = player->box.y - SIDE/2;
                int pexe_left = land->fish1->box.x - SIDE/2;
                int pexe_foot = land->fish1->box.y + SIDE/2;

                if (right >= pexe_left && foot <= pexe_foot && head <= pexe_foot) {
                        land->fish1->collected = 1;
                        return 1;
                }
        }       
        return 0;
}

int fish2_taken(cat *player, world *land) {
        if (!player || !land)
                return -1;


        if (!land->fish2->collected) {

                int right =player->box.x + SIDE/2;
                int foot = player->box.y + SIDE/2;
                int head = player->box.y - SIDE/2;
                int pexe_left = land->fish2->box.x - SIDE/2;
                int pexe_foot = land->fish2->box.y + SIDE/2;
        
                if (right >= pexe_left && foot <= pexe_foot && head <= pexe_foot) {
                        land->fish2->collected = 1;
                        return 1;
                }
        }       
        return 0;
}
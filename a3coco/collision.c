#include <stdio.h>
#include "collision.h"

int floor_collision(cat *player, world *land) {
        if (!player || !land)
                return -1;

        int old_foot = player->old_y + player->box.side / 2;
        int new_foot = player->box.y + player->box.side / 2;

        for (int i = 0; i < NUM_SOLIDS; i++) {
                struct solid s = land->solids[i];

                if (player->box.x >= s.x && 
                    player->box.x <= s.x + s.width && 
                    old_foot <= s.y && new_foot >= s.y) {
                        player->box.y = s.y - player->box.side / 2;
                        player->vel_y = 0;
                        //printf("return do floor 1\n");
                        return 1;
                    }
        }

    return 0;
}

//tentei q fazer caso geral p qualuqer tipo de wall mas tive q foca rno meumapa
//pq como eu fiz vetor e dificil verificar todos os blocos ao msm tempo

void wall_collision(cat *player, world *land, int vale) {
        if (!player || !land)
                return;

        int left  = player->box.x - player->box.side/2;
        int right = player->box.x + player->box.side/2;

        if (vale == 1) {
                struct solid wall_esq = land->solids[0];
                struct solid wall_dir = land->solids[3];

                if (left <= (wall_esq.x + wall_esq.width)) {
                        player->box.x = (wall_esq.x + wall_esq.width) + player->box.side/2;
                }
                if (right >= wall_dir.x) {
                        printf("ESTA ENCOSTANDO NA PAREDE!!!!!!!!\n");
                        player->box.x = wall_dir.x - player->box.side/2;
                }
        }

        else if (vale == 2) {
                struct solid wall_esq = land->solids[3];
                struct solid wall_dir = land->solids[5];

                if (left <= (wall_esq.x + wall_esq.width))
                        player->box.x = (wall_esq.x + wall_esq.width) + player->box.side/2;
                if (right >= wall_dir.x)
                        player->box.x = wall_dir.x - player->box.side/2;
        }

        else if (vale == 3) {
                struct solid wall_esq1 = land->solids[5];
                struct solid wall_esq2 =  land->solids[6];
                struct solid wall_esq3 =  land->solids[7];
                struct solid wall_dir = land->solids[10];

                if (left <= (wall_esq1.x + wall_esq1.width))
                        player->box.x = (wall_esq1.x + wall_esq1.width) + player->box.side/2;

                else if (left <= (wall_esq2.x + wall_esq2.width))
                        player->box.x = (wall_esq2.x + wall_esq2.width) + player->box.side/2;

                else if (left <= (wall_esq3.x + wall_esq3.width))
                        player->box.x = (wall_esq3.x + wall_esq3.width) + player->box.side/2;

                if (right >= wall_dir.x)
                        player->box.x = wall_dir.x - player->box.side/2;
        }
}

int hazard_collision(cat *player, world *land, int *instakill) {
        if (!player || !land)
                return 0;

        int left  = player->box.x - player->box.side/2;
        int right = player->box.x + player->box.side/2;
        int head  = player->box.y - player->box.side/2;
        int foot = player->box.y + player->box.side / 2;

        for (int i = 0; i < NUM_HAZARDS; i++) {
                struct hazard s = land->hazards[i];
                
                if (right > s.x && left < s.x + s.width &&
                foot > s.y && head < s.y + s.height) {
                        //verifica se o dano eh de buraco lava ou espinho instakill;
                        if (s.y > 488)
                                *instakill = 1;
                        return 1;
                }
        }
        
        return -1;
}

int entity_collision (struct body a, struct body b) {
    if (a.x + a.side/2 < b.x - b.side/2)
        return 0;

    if (a.x - a.side/2 > b.x + b.side/2)
        return 0;

    if (a.y + a.side/2 < b.y - b.side/2)
        return 0;

    if (a.y - a.side/2 > b.y + b.side/2)
        return 0;

    return 1;
}
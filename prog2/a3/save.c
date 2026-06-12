#include <stdio.h>
#include "save.h"
#include "game.h"

#define SAVE_FILE "save.cat"

// estrutura que define os dados gravados em disco
// apenas o essencial para restaurar o estado do jogo
typedef struct {
        int player_x;
        int player_y;
        int player_hp;
        int fish1_collected;
        int fish2_collected;
        int fox1_x;
        int fox2_x;
        int bird_x;

        int platform_x;
        int platform_vel_x;
} save_data;

int save_exists() {
        FILE *f = fopen(SAVE_FILE, "rb");
        if (!f) 
                return 0;

        fclose(f);
        return 1;
}

void save_game(struct game *catland) {
        FILE *f = fopen(SAVE_FILE, "wb");
        if (!f) 
                return;

        save_data data = {
                .player_x       = catland->player->box.x,
                .player_y       = catland->player->box.y,
                .player_hp      = catland->player->hp,
                .fish1_collected = catland->land->fish1->collected,
                .fish2_collected = catland->land->fish2->collected,
                .fox1_x         = catland->land->fox1->box.x,
                .fox2_x         = catland->land->fox2->box.x,
                .bird_x         = catland->land->bird->box.x,

                .platform_x      = catland->land->move[0].x,
                .platform_vel_x  = catland->land->move[0].vel_x
        };

        fwrite(&data, sizeof(save_data), 1, f);
        fclose(f);
}

void load_game(struct game *catland) {
        FILE *f = fopen(SAVE_FILE, "rb");
        if (!f) 
                return;

        save_data data;
        fread(&data, sizeof(save_data), 1, f);
        fclose(f);

        catland->player->box.x      = data.player_x;
        catland->player->box.y      = data.player_y;
        catland->player->hp         = data.player_hp;
        catland->land->fish1->collected = data.fish1_collected;
        catland->land->fish2->collected = data.fish2_collected;
        catland->land->fox1->box.x  = data.fox1_x;
        catland->land->fox2->box.x  = data.fox2_x;
        catland->land->bird->box.x  = data.bird_x;

        // carrega a posicao que a plataforma movel estava no save
        catland->land->move[0].x        = data.platform_x;
        catland->land->move[0].vel_x    = data.platform_vel_x;
}
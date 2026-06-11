#include <stdio.h>
#include <allegro5/allegro5.h>	
#include "game.h"
#include "camera.h"
#include "cat.h"
#include "physics.h"

void render_menu(struct game *catland) {
        if (!catland)
                return;

        // carrega o fundo do menu e o titulo
        al_draw_bitmap(catland->images->menu_bg, 0, 0, 0);
        al_draw_text(catland->font->menu, al_map_rgb(255, 255, 255), X_SCREEN/2, 12, ALLEGRO_ALIGN_CENTER, "CATLAND");

        // carrega o primeiro botao pra jogar
        al_draw_scaled_bitmap(catland->images->button, 0, 0, al_get_bitmap_width(catland->images->button), al_get_bitmap_height(catland->images->button), 212, 247, 288, 138, 0);
        al_draw_text(catland->font->game, al_map_rgb(220, 211, 230), 350, 250, ALLEGRO_ALIGN_CENTER, "JOGAR");

        // carrega o segundo botao pra sair
        al_draw_scaled_bitmap(catland->images->button, 0, 0, al_get_bitmap_width(catland->images->button), al_get_bitmap_height(catland->images->button), 212, 320, 288, 138, 0);
        al_draw_text(catland->font->game, al_map_rgb(220, 211, 230), 350, 323, ALLEGRO_ALIGN_CENTER, "SAIR");

        return;
}

void input_menu(struct game *catland) {
        int cursor_x = catland->event.mouse.x;
        int cursor_y = catland->event.mouse.y;

        // verifica se clicou na area do botao jogar
        if (cursor_x >= 215 && cursor_x <= 500 && cursor_y >= 247 && cursor_y <= 318) {
                al_play_sample(catland->music->click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                catland->state = PLAY;
        }

        // verifica se clicou na area do botao sair
        if (cursor_x >= 215 && cursor_x <= 490 && cursor_y >= 323 && cursor_y <= 390) {
                al_play_sample(catland->music->click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                //espera o som toca por completo antes de sair
                al_rest(0.5);
                catland->state = EXIT;
        }
}

void render_play(struct game *catland) {
        if (!catland)
                return;

        apply_gravity(catland->player, catland->land);
        apply_sounds(catland);
        update_all(catland);
        draw_all(catland);
        
        cat *p = catland->player;
        // escolhe o sprite
        ALLEGRO_BITMAP *sprite;
        switch (p->frame) {
                case WALK:
                        p->sprite_counter++;
                        if (p->sprite_counter >= WALK_SPRITE * 5)
                                p->sprite_counter = 0;
                        sprite = p->sprites->walk[p->sprite_counter / 5];
                        break;
                case RUN:
                        p->sprite_counter++;
                        if (p->sprite_counter >= RUN_SPRITE * 5)
                                p->sprite_counter = 0;
                        sprite = p->sprites->run[p->sprite_counter / 5];
                        break; 
                case JUMP:
                        p->sprite_counter++;
                        if (p->sprite_counter >= JUMP_SPRITE * 4)
                                p->sprite_counter = 0;
                        sprite = p->sprites->jump[p->sprite_counter / 4];
                        break;
                case SCARED:
                        sprite = p->sprites->scared;
                        break;
                case DOWN:
                        sprite = p->sprites->crouch;
                        break;               
                default:
                        sprite = p->sprites->normal;
                        break;
        }

        int flip = 0;

        //se tive olhando p esquerda deixa sprite p esquerda (flag = 1);
        if (p->box.face == LOOK_LEFT) 
                flip = 1;

        al_draw_scaled_bitmap(sprite, 0, 0, 50, 50, (p->box.x - SIDE_CAT/2) -catland->player->camera->x, p->box.y - SIDE_CAT/2, 64, 64, flip);

        if (!cat_alive(p) && !p->cooldown.death_timer) 
                catland->state = GAMEOVER;
}

void input_gameover(struct game *catland) {
        if (!catland)
                return;

        int cursor_x = catland->event.mouse.x;
        int cursor_y = catland->event.mouse.y;

        // verifica se clicou na area do botao  recomecar
        if (cursor_x >= 215 && cursor_x <= 500 && cursor_y >= 247 && cursor_y <= 318) {
                al_play_sample(catland->music->click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                reset_game(catland);
                catland->state = PLAY;
        }

        // verifica se clicou na area do botao sair
        if (cursor_x >= 215 && cursor_x <= 490 && cursor_y >= 323 && cursor_y <= 390) {
                al_play_sample(catland->music->click, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                //espera o som toca por completo antes de sair
                al_rest(0.5);
                catland->state = EXIT;
        }
        
}

void render_gameover(struct game *catland) {
        if (!catland)
                return;

        // carrega o fundo do menu e o titulo
        al_draw_bitmap(catland->images->menu_bg, 0, 0, 0);
        al_draw_text(catland->font->menu, al_map_rgb(255, 255, 255), X_SCREEN/2, 15, ALLEGRO_ALIGN_CENTER, "GAME");
        al_draw_text(catland->font->menu, al_map_rgb(255, 255, 255), X_SCREEN/2, 115, ALLEGRO_ALIGN_CENTER, "OVER");

        // carrega o primeiro botao pra jogar
        al_draw_scaled_bitmap(catland->images->button, 0, 0, al_get_bitmap_width(catland->images->button), al_get_bitmap_height(catland->images->button), 212, 247, 288, 138, 0);
        al_draw_text(catland->font->game, al_map_rgb(220, 211, 230), 350, 250, ALLEGRO_ALIGN_CENTER, "RECOMEÇAR");

        // carrega o segundo botao pra sair
        al_draw_scaled_bitmap(catland->images->button, 0, 0, al_get_bitmap_width(catland->images->button), al_get_bitmap_height(catland->images->button), 212, 320, 288, 138, 0);
        al_draw_text(catland->font->game, al_map_rgb(220, 211, 230), 350, 323, ALLEGRO_ALIGN_CENTER, "SAIR");

        return;
}

#include <stdio.h>
#include <allegro5/allegro5.h>	
#include "game.h"
#include "camera.h"
#include "cat.h"

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
        int flip = 0;
        cat *p = catland->player;
        printf(" x = %d y = %d\n", p->box.x, p->box.y); //debug
        update_camera(p->camera, p->box.x);
        float cam = p->camera->x;
        cat_gravity(p, catland->land);
        update_position(p, catland->land);





        // define qual animação deve estar ativa
        if (p->control->crouch)
                p->frame = DOWN;
        else if (p->control->jump)
                p->frame = JUMP;
        else if (p->control->run && (p->control->left || p->control->right))
                p->frame = RUN;
        else if (p->control->left || p->control->right)
                p->frame = WALK;
        else
                p->frame = NORMAL; 

        // desenha fundo e mundo (o background vai mais devagar dando um efeito top)
        al_draw_bitmap(catland->images->game_bg, -cam * 0.3, 0, 0);
        al_draw_bitmap(catland->images->land, -cam, 0, 0);
        
        // desenha o pexe
        al_draw_scaled_bitmap(catland->land->fish1->sprite, 0, 0, SIDE_FISH, SIDE_FISH, (catland->land->fish1->box.x - SIDE_FISH/2) - cam, catland->land->fish1->box.y - SIDE_FISH/2, 45, 45, 0);
        al_draw_scaled_bitmap(catland->land->fish2->sprite, 0, 0, SIDE_FISH, SIDE_FISH, (catland->land->fish2->box.x - SIDE_FISH/2) - cam, catland->land->fish2->box.y - SIDE_FISH/2, 45, 45, 0);        
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
                        if (p->sprite_counter >= JUMP_SPRITE * 5)
                                p->sprite_counter = 0;
                        sprite = p->sprites->jump[p->sprite_counter / 5];
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

        //se tive olhando p esquerda deixa sprite p esquerda (flag = 1);
        if (p->box.face == LOOK_LEFT) 
                flip = 1;

        al_draw_scaled_bitmap(sprite, 0, 0, 50, 50, (p->box.x - SIDE_CAT/2) - cam, p->box.y - SIDE_CAT/2, 64, 64, flip);
}

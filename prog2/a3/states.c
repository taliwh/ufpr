#include <stdio.h>
#include <allegro5/allegro5.h>	
#include "game.h"

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
        if (cursor_x >= 215 && cursor_x <= 500 && cursor_y >= 247 && cursor_y <= 318)
                catland->state = PLAY;
        
        // verifica se clicou na area do botao sair
        if (cursor_x >= 215 && cursor_x <= 490 && cursor_y >= 323 && cursor_y <= 390)
                catland->state = EXIT;
}

void render_play() {
        
}


/*
void state_play(struct game *catland);
void state_win(struct game *catland);
void state_gameover(struct game *catland);
*/
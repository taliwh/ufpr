#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>

#include "game.h"
#include "cat.h"
#include "land.h"

// cria o mundo do jogo 
struct game *create_game () {
        // aloca o que precisa ser alocado
        struct game *catland = malloc(sizeof(struct game));
        if (!catland)
                return NULL;
        
        catland->land = create_land();

        catland->music = malloc(sizeof(struct sounds));
        catland->font = malloc(sizeof(struct fonts));
        catland->images = malloc(sizeof(struct pngs));
        if (!catland->music || !catland->font || !catland->images) {
                free(catland->music);
                free(catland->font);
                free(catland->images);
                free(catland);
                return NULL;
        }

        // carrega as musicas necessarias
        catland->music->default = al_load_audio_stream("assets/musica/default.mp3", 4, 2048);
        catland->music->death = al_load_audio_stream("assets/musica/death.mp3", 4, 2048);
        catland->music->click = al_load_audio_stream("assets/musica/click.mp3", 4, 2048);
        catland->music->fish = al_load_audio_stream("assets/musica/fish.mp3", 4, 2048);
        catland->music->damage = al_load_audio_stream("assets/musica/dano.mp3", 4, 2048);

        // carrega as fontes necessarias
        catland->font->menu = al_load_ttf_font("assets/fontes/menu.otf", 128, 0);
        catland->font->game = al_load_ttf_font("assets/fontes/default.ttf", 60, 0);

        // carrega as imagens necessarias
        catland->images->icon = al_load_bitmap("assets/sprites/game/icon.png");
        catland->images->land = al_load_bitmap("assets/sprites/land.png");
        catland->images->menu_bg = al_load_bitmap("assets/sprites/menu.png");
        catland->images->game_bg = al_load_bitmap("assets/sprites/galaxy.png");
        catland->images->button = al_load_bitmap("assets/sprites/botao.png");
        catland->images->heart = al_load_bitmap("assets/sprites/heart.png");

        // define o fps e a resolucao do jogo, juntamente com a fila de eventos
        catland->timer = al_create_timer(1.0 / 30.0);
        catland->queue = al_create_event_queue();
        catland->disp = al_create_display(X_SCREEN, Y_SCREEN);

        // estado inicial do jogo
        catland->state = MENU;

        // cria o player
        catland->player = create_cat(CAT_SIDE, LOOK_RIGHT, CAT_SIDE/2, Y_FLOOR, LAND_WIDTH, Y_SCREEN);
        if (!catland->player)
                return NULL;

        return catland;
}
                 
void destroy_image (struct game* catland) {
        al_destroy_bitmap(catland->images->icon);
        al_destroy_bitmap(catland->images->land);
        al_destroy_bitmap(catland->images->menu_bg);
        al_destroy_bitmap(catland->images->game_bg);
        al_destroy_bitmap(catland->images->button);
        al_destroy_bitmap(catland->images->heart);

        free(catland->images);
}

void destroy_font (struct game* catland) {
        al_destroy_font(catland->font->menu);
        al_destroy_font(catland->font->game);

        free(catland->font);        
}

void destroy_audio (struct game* catland) {
        al_destroy_audio_stream(catland->music->default);
        al_destroy_audio_stream(catland->music->death);
        al_destroy_audio_stream(catland->music->click);
        al_destroy_audio_stream(catland->music->fish);
        al_destroy_audio_stream(catland->music->damage);

        free(catland->music);
}

void destroy_game (struct game* catland) {
        if (!catland)
                return;

        destroy_cat(catland->player);
        destroy_image(catland);
        destroy_font(catland);
        destroy_audio(catland);

        al_destroy_timer(catland->timer);
        al_destroy_event_queue(catland->queue);
        al_destroy_display(catland->disp);

        destroy_land(catland->land);
        free(catland);
}



create_camera
destroy_camera
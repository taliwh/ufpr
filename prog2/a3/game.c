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
#include "physics.h"
#include "camera.h"

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
                free(catland->land);
                free(catland);
                return NULL;
        }

        // carrega trilhas e efeitos sonoros
        catland->music->default_music = al_load_audio_stream("assets/musica/default.ogg", 4, 2048);
        catland->music->win = al_load_audio_stream("assets/musica/win.ogg", 4, 2048);
        catland->music->gameover = al_load_audio_stream("assets/musica/gameover.ogg", 4, 2048);
        catland->music->death = al_load_sample("assets/musica/death.ogg");
        catland->music->click = al_load_sample("assets/musica/click.ogg");
        catland->music->fish = al_load_sample("assets/musica/fish.ogg");
        catland->music->damage = al_load_sample("assets/musica/dano.ogg");


        // carrega as fontes necessarias
        catland->font->menu = al_load_ttf_font("assets/fontes/default.otf", 128, 0);
        catland->font->game = al_load_ttf_font("assets/fontes/default.otf", 60, 0);
        catland->font->contador = al_load_ttf_font("assets/fontes/ARCADECLASSIC.TTF", 30, 0);

        // carrega as imagens necessarias
        catland->images->icon = al_load_bitmap("assets/sprites/game/icon.png");
        catland->images->land = al_load_bitmap("assets/sprites/land.png");
        catland->images->menu_bg = al_load_bitmap("assets/sprites/menu.png");
        catland->images->game_bg = al_load_bitmap("assets/sprites/galaxy.png");
        catland->images->button = al_load_bitmap("assets/sprites/botao.png");
        catland->images->heart = al_load_bitmap("assets/sprites/heart.png");
        catland->images->platform = al_load_bitmap("assets/sprites/platform.png");

        // define o fps e a resolucao do jogo, juntamente com a fila de eventos
        catland->timer = al_create_timer(1.0 / 30.0);
        catland->queue = al_create_event_queue();
        catland->disp = al_create_display(X_SCREEN, Y_SCREEN);

        ALLEGRO_BITMAP *icon = al_load_bitmap("assets/sprites/game/icon.png");
        if (icon)
                al_set_display_icon(catland->disp, icon);

        // estado inicial do jogo
        catland->state = MENU;
        catland->last_state = MENU;

        // cria o player
        catland->player = create_cat(LOOK_RIGHT, 0, Y_FLOOR - SIDE, LAND_WIDTH, Y_SCREEN);
        if (!catland->player)
                return NULL;

        return catland;
}

void init_allegro() {
        al_init();

        al_install_keyboard();
        al_install_mouse();
        al_install_audio();

        al_init_image_addon();
        al_init_acodec_addon();
        al_init_font_addon();
        al_init_ttf_addon();

        al_reserve_samples(16);
}

void set_allegro(struct game *catland) {
        if (!catland)
                return;

	al_register_event_source(catland->queue, al_get_keyboard_event_source());				
	al_register_event_source(catland->queue, al_get_display_event_source(catland->disp));				
	al_register_event_source(catland->queue, al_get_timer_event_source(catland->timer)); 
	al_register_event_source(catland->queue, al_get_mouse_event_source());	
        
        al_start_timer(catland->timer);
}

void apply_sounds (struct game *catland) {
        if (!catland)
                return;

        cat *p = catland->player;
        
        // efeitos sonoros de evento unico
        if (p->cooldown.took_fish) {
                al_play_sample(catland->music->fish, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                p->cooldown.took_fish = 0;
        }

        if (p->cooldown.took_damage) {
                al_play_sample(catland->music->damage, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                p->cooldown.took_damage = 0;
        }

        if (p->cooldown.just_died) {
                al_play_sample(catland->music->death, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                p->cooldown.just_died = 0;
        }

        // musica de fundo durante o jogo
        if (catland->state == PLAY) {
                al_set_audio_stream_playing(catland->music->win, false);
                al_set_audio_stream_playing(catland->music->gameover, false);
                if (catland->last_state == GAMEOVER || catland->last_state == WIN)
                        al_seek_audio_stream_secs(catland->music->default_music, 0.0); 
                al_set_audio_stream_playmode(catland->music->default_music, ALLEGRO_PLAYMODE_LOOP);
                al_set_audio_stream_gain(catland->music->default_music, 0.10);
                al_set_audio_stream_playing(catland->music->default_music, true);
                al_attach_audio_stream_to_mixer(catland->music->default_music, al_get_default_mixer());
        }

        // musica de gameover
        if (catland->state == GAMEOVER) {
                al_set_audio_stream_playing(catland->music->default_music, false);
                if (catland->last_state == PLAY)
                        al_seek_audio_stream_secs(catland->music->gameover, 0.0);
                al_set_audio_stream_playmode(catland->music->gameover, ALLEGRO_PLAYMODE_LOOP);
                al_set_audio_stream_gain(catland->music->gameover, 0.10);
                al_set_audio_stream_playing(catland->music->gameover, true);
                al_attach_audio_stream_to_mixer(catland->music->gameover, al_get_default_mixer());
        }

        // musica de vitoria (toca 1 vez)
        if (catland->state == WIN) {
                al_set_audio_stream_playing(catland->music->default_music, false);
                if (catland->last_state == PLAY)
                        al_seek_audio_stream_secs(catland->music->win, 0.0); 
                al_set_audio_stream_playmode(catland->music->win, ALLEGRO_PLAYMODE_ONCE);
                al_set_audio_stream_gain(catland->music->win, 0.10);
                al_set_audio_stream_playing(catland->music->win, true);
                al_attach_audio_stream_to_mixer(catland->music->win, al_get_default_mixer());
        }

        // atualiza o estado anterior
        catland->last_state = catland->state;
}

void update_all(struct game *catland) {
        if (!catland)
                return;

        update_land(catland->land);
        update_camera(catland->player->camera, catland->player->box.x);
        update_frame(catland->player);
        update_position(catland->player, catland->land);
        update_hp(catland->player, catland->land);
        update_fox(catland->land->fox1);
        update_fox(catland->land->fox2);
        update_bird(catland->land->bird);
}

void draw_all (struct game *catland) {
        if (!catland)
                return;

        float cam = catland->player->camera->x;

        // o fundo se move mais devagar que o mundo
        al_draw_bitmap(catland->images->game_bg, -cam * 0.3, 0, 0);
        al_draw_bitmap(catland->images->land, -cam, 0, 0);

        // renderiza plataformas moveis
        for (int i = 0; i < NUM_SOLIDS_MOVE; i++) {
                struct solid_move *s = &catland->land->move[i];
                al_draw_bitmap(catland->images->platform, s->x - cam, s->y, 0);
        }

        // renderiza os peixes que nao foram coletados
        if (!catland->land->fish1->collected)
                al_draw_scaled_bitmap(catland->land->fish1->sprite, 0, 0, 16, 16, (catland->land->fish1->box.x - SIDE/2) - cam, catland->land->fish1->box.y - SIDE/2, 45, 45, 0);
        if (!catland->land->fish2->collected)
                al_draw_scaled_bitmap(catland->land->fish2->sprite, 0, 0, 16, 16, (catland->land->fish2->box.x - SIDE/2) - cam, catland->land->fish2->box.y - SIDE/2, 45, 45, 0);        

        // renderiza os inimigos
        draw_fox(catland->land->fox1, cam);
        draw_fox(catland->land->fox2, cam);
        draw_bird(catland->land->bird, cam);

        // desenha os coracoes nao deixando com que o player tenha mais que 5 vidas
        if (catland->player->hp > 5)
                catland->player->hp = 5;
        for (int i = 0; i < catland->player->hp; i++) {
                al_draw_scaled_bitmap(catland->images->heart,
                        0, 0,
                        al_get_bitmap_width(catland->images->heart),
                        al_get_bitmap_height(catland->images->heart),
                        10 + i * 40, 10,   
                        32, 32,            
                        0);
        }
        
        int fish_count = catland->land->fish1->collected + catland->land->fish2->collected;
 
        // desenha sprite do peixe 1 (clownfish) no canto superior direito
        al_draw_scaled_bitmap(catland->land->fish1->sprite, 0, 0, 16, 16, X_SCREEN - 90, 10, 36, 36,0);
 
        // desenha o contador de quantos peixes ja foram coletados
        char fish_text[8]; 
        sprintf(fish_text, "x%d", fish_count); // sprintf converte fish_count para string pois al_draw_text nao aceita numero
        al_draw_text(catland->font->contador, al_map_rgb(255, 255, 255), X_SCREEN - 48, 12, 0, fish_text);

}

void reset_game(struct game *catland) {
        if (!catland)
                return;

        destroy_cat(catland->player);
        destroy_land(catland->land);

        catland->player = create_cat(LOOK_RIGHT, 0, Y_FLOOR - SIDE, LAND_WIDTH, Y_SCREEN);
        catland->land = create_land();

        if (!catland->player || !catland->land)
                catland->state = EXIT;
}

void destroy_game (struct game* catland) {
        if (!catland)
                return;

        destroy_cat(catland->player);
        destroy_image(catland);
        destroy_font(catland);
        destroy_audio(catland);
        destroy_land(catland->land);

        al_destroy_timer(catland->timer);
        al_destroy_event_queue(catland->queue);
        al_destroy_display(catland->disp);

        free(catland);
}

void destroy_image (struct game* catland) {
        if (!catland)
                return;

        al_destroy_bitmap(catland->images->icon);
        al_destroy_bitmap(catland->images->land);
        al_destroy_bitmap(catland->images->menu_bg);
        al_destroy_bitmap(catland->images->game_bg);
        al_destroy_bitmap(catland->images->button);
        al_destroy_bitmap(catland->images->heart);
        al_destroy_bitmap(catland->images->platform);

        free(catland->images);
}

void destroy_font (struct game* catland) {
        if (!catland)
                return;

        al_destroy_font(catland->font->menu);
        al_destroy_font(catland->font->game);
        al_destroy_font(catland->font->contador);

        free(catland->font);        
}

void destroy_audio (struct game* catland) {
        if (!catland)
                return;

        al_destroy_audio_stream(catland->music->default_music);
        al_destroy_audio_stream(catland->music->win);
        al_destroy_audio_stream(catland->music->gameover);

        al_destroy_sample(catland->music->death);
        al_destroy_sample(catland->music->click);
        al_destroy_sample(catland->music->fish);
        al_destroy_sample(catland->music->damage);

        free(catland->music);
}




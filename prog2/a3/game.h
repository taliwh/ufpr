#ifndef __GAME__
#define __GAME__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "cat.h"
#include "land.h"

#define X_SCREEN 700																																									//Definição do tamanho da tela em pixels no eixo x
#define Y_SCREEN 512

enum state {
        MENU,
        PLAY,
        WIN,
        GAMEOVER,
        EXIT,
};

struct fonts {
        ALLEGRO_FONT *menu;
        ALLEGRO_FONT *game;
};

struct sounds {
        ALLEGRO_AUDIO_STREAM *default_music;
        ALLEGRO_SAMPLE *death;
        ALLEGRO_SAMPLE *click;
        ALLEGRO_SAMPLE *fish;
        ALLEGRO_SAMPLE *damage;
};

struct pngs {
        ALLEGRO_BITMAP *icon;
        ALLEGRO_BITMAP *land;
        ALLEGRO_BITMAP *menu_bg;
        ALLEGRO_BITMAP *game_bg;
        ALLEGRO_BITMAP *button;
        ALLEGRO_BITMAP *heart;
};

/*      definicoes gerais do jogo:
        vetores : trilha sonora, imagens, fontes
        

*/
struct game {
        struct sounds *music;
        struct pngs *images;
        struct fonts *font;         
        ALLEGRO_EVENT event;    
        ALLEGRO_TIMER *timer;   // clock dos eventos   
        ALLEGRO_EVENT_QUEUE *queue;  
        ALLEGRO_DISPLAY *disp;   
        world *land;
        enum state state;  
        cat *player;       
};

struct game* create_game();
void init_allegro();
void apply_sounds (struct game *catland);
void set_allegro(struct game *catland);
void update_all(struct game *catland);
void draw_all (struct game *catland);
void reset_game(struct game *catland);
void destroy_game(struct game* catland);
void destroy_image(struct game* catland);
void destroy_font(struct game* catland);
void destroy_audio(struct game* catland);
void destroy_game(struct game* catland);

#endif




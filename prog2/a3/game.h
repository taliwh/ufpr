#ifndef __GAME__
#define __GAME__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define X_SCREEN 700																																									//Definição do tamanho da tela em pixels no eixo x
#define Y_SCREEN 512

enum state {
        MENU,
        GAMEOVER,
        QUIT,
};

struct fonts {
        ALLEGRO_FONT *menu;
        ALLEGRO_FONT *game;
};

struct sounds {
        ALLEGRO_AUDIO_STREAM *default;
        ALLEGRO_AUDIO_STREAM *death;
        ALLEGRO_AUDIO_STREAM *click;
        ALLEGRO_AUDIO_STREAM *fish;
        ALLEGRO_AUDIO_STREAM *damage;
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
        enum state state;  
        cat *player;       
};


struct catland *creat_land

void destroy_land

funcao  MENU
funcao vitoria
funcao GAMEOVER
funcao gameplay 
? vetor imagem?
funcao inimigo e player

#endif




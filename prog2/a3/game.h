#ifndef __GAME__
#define __GAME__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "cat.h"
#include "land.h"

// dimensoes da tela
#define X_SCREEN 700																																									//Definição do tamanho da tela em pixels no eixo x
#define Y_SCREEN 512

// estados possiveis do jogo
enum state {
        MENU,
        PLAY,
        WIN,
        GAMEOVER,
        PAUSE,
        EXIT,
};

// fontes
struct fonts {
        ALLEGRO_FONT *menu;
        ALLEGRO_FONT *game;
        ALLEGRO_FONT *contador;
};

// musica e efeitos sonoros
struct sounds {
        ALLEGRO_AUDIO_STREAM *default_music;
        ALLEGRO_AUDIO_STREAM *win;
        ALLEGRO_AUDIO_STREAM *gameover;
        ALLEGRO_SAMPLE *death;
        ALLEGRO_SAMPLE *click;
        ALLEGRO_SAMPLE *fish;
        ALLEGRO_SAMPLE *damage;
};

// paisagem e outros
struct pngs {
        ALLEGRO_BITMAP *icon;
        ALLEGRO_BITMAP *land;
        ALLEGRO_BITMAP *menu_bg;
        ALLEGRO_BITMAP *game_bg;
        ALLEGRO_BITMAP *button;
        ALLEGRO_BITMAP *heart;
        ALLEGRO_BITMAP *platform;
};

// definicoes gerais do jogo
struct game {
        struct sounds *music;         // trilha sonora
        struct pngs *images;          // imagens
        struct fonts *font;           // fontes para texto
        world *land;                  // universo do jogo
        cat *player;                  // jogador
        enum state state;             // estado atual
        enum state last_state;        // estado anterior
        ALLEGRO_EVENT event;          // evento 
        ALLEGRO_TIMER *timer;         // clock (30 fps)
        ALLEGRO_EVENT_QUEUE *queue;   // fila de eventos
        ALLEGRO_DISPLAY *disp;        // display
};

// aloca e inicializa todos os recursos do jogo: mundo, sons, fontes, imagens e player
struct game* create_game();

// inicializa o necessario da biblioteca allegro para o jogo
void init_allegro();
void set_allegro(struct game *catland);

// toca os efeitos sonoros pontuais e gerencia a musica de fundo
// troca a trilha conforme o estado atual do jogo, reiniciando ao mudar de estado
void apply_sounds (struct game *catland);

// atualiza todos os elementos do jogo em cada frame
void update_all(struct game *catland);

// renderiza o fundo, o mundo, os inimigos, os peixes e o hp do player
void draw_all (struct game *catland);

// destroi o player e o mundo atual, recriando tudo do zero
void reset_game(struct game *catland);

// libera toda a memoria alocada pelo jogo
void destroy_game(struct game* catland);
void destroy_image(struct game* catland);
void destroy_font(struct game* catland);
void destroy_audio(struct game* catland);

#endif




#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "game.h"
#include "cat.h"
#include "land.h"

// cria o mundo do jogo 
struct game *create_game()
{
        // aloca o que precisa ser alocado
        struct game *catland = malloc(sizeof(struct game));
        if (!catland)
                return NULL;
        
        catland->music = malloc(sizeof(struct sounds));
        catland->font = malloc(sizeof(struct fonts));
        catland->images = malloc(sizeof(struct pngs));
        if (!catland->music || !catland->font || !catland->images)
                return NULL;
        
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
        catland->images->land = al_load_bitmap("assets/sprites/land/.png");
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
        catland->player = cat_create(CAT_SIDE, LOOK_RIGHT, CAT_SIDE/2, Y_FLOOR, LAND_WIDTH, Y_SCREEN);
        if (!catland->player)
                return NULL;

        return catland;
}
                 
void destroy_game
run_game
destruir jogo

fazer estado jogo
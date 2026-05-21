#include <allegro5/allegro5.h>													
#include <allegro5/allegro_font.h> //fontes allegro									
#include <allegro5/allegro_ttf.h> //minhas fontes ttf

#include "cat.h"

#define X_SCREEN 640																																										//Definição do tamanho da tela em pixels no eixo x
#define Y_SCREEN 480

int main() {
        al_init();
        al_install_keyboard();

        ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); //30 fps
        ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //fila de eventos

        ALLEGRO_FONT* font_menu = al_load_ttf_font("assets/fontes/Mocha Choco.otf", 32, 0);
        ALLEGRO_FONT* font = al_create_builtin_font();

        ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN);

        cat* player = cat_create()

        if (!player)
                return 1;

        
        
                




}
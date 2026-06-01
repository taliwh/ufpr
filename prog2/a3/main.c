#include <allegro5/allegro5.h>																					
#include <allegro5/allegro_ttf.h> //minhas fontes ttf

#include "cat.h"
#include "game.h"

int main() {
        al_init();
        al_install_keyboard();
        al_init_font_addon();
        al_init_ttf_addon();

        struct game *catland = create_game();

	al_register_event_source(catland->queue, al_get_keyboard_event_source());				
	al_register_event_source(catland->queue, al_get_display_event_source(catland->disp));				
	al_register_event_source(catland->queue, al_get_timer_event_source(catland->timer)); 
	al_register_event_source(catland->queue, al_get_mouse_event_source());	

        ALLEGRO_EVENT event;
        al_start_timer(timer);
        bool redraw;

        while (event.type != ALLEGRO_EVENT_DISPLAY_CLOSE && catland->state != EXIT) {
                al_wait_for_event(catland->queue, &event);

                if (event.type == ALLEGRO_EVENT_TIMER)
                        redraw = true; 
                
                else if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP) 

                        
                
                if (redraw && al_is_event_queue_empty(catland->queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));		
                        switch (catland->state)
                        {
                        case (MENU):
                                start_state_menu(catland);

                        case (PLAY):
                                start_state_play(catland);
                                break;
                        case (GAMEOVER):
                                start_state_catlandover(catland);
                                break;
                        case (WIN):
                                start_state_win(catland);
                                break;
                        default:
                                break;
                        }                        							
    		        al_flip_display();
                        redraw = false;									
		}

		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
                        break;	
        }

        destroy_game(catland);

	return 0;
}
        
        
                





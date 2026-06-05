#include <allegro5/allegro5.h>																					
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
 
#include "cat.h"
#include "game.h"
#include "states.h"

int main() {
        al_init();
        al_install_keyboard();
        al_install_mouse();
        al_init_image_addon();
        al_install_audio();
        al_init_acodec_addon();
        al_init_font_addon();
        al_init_ttf_addon();
        al_reserve_samples(16);

        struct game *catland = create_game();
        if (!catland)
                return 1;

	al_register_event_source(catland->queue, al_get_keyboard_event_source());				
	al_register_event_source(catland->queue, al_get_display_event_source(catland->disp));				
	al_register_event_source(catland->queue, al_get_timer_event_source(catland->timer)); 
	al_register_event_source(catland->queue, al_get_mouse_event_source());	

        al_set_audio_stream_playmode(catland->music->default_music, ALLEGRO_PLAYMODE_LOOP);
        al_attach_audio_stream_to_mixer(catland->music->default_music, al_get_default_mixer());
        al_set_audio_stream_gain(catland->music->default_music, 0.05);
        al_set_audio_stream_playing(catland->music->default_music, true);

        al_start_timer(catland->timer);
        while (catland->state != EXIT) {
                al_wait_for_event(catland->queue, &catland->event);
                if (catland->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        catland->state = EXIT;
                if (catland->event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(catland->queue)) {
                        al_clear_to_color(al_map_rgb(0,0,0));
                        switch (catland->state)
                        {
                                case (MENU):
                                        state_menu(catland);
                                        break;
                                /*
                                case (PLAY):
                                        state_play(catland);
                                        break;
                                case (WIN):
                                        state_win(catland);
                                        break;
                                case (GAMEOVER):
                                        state_gameover(catland);
                                        break;
                                */
                                default:
                                        break;
                        }                        							
    		        al_flip_display();							
		}
        }

        destroy_game(catland);
	return 0;
}
        
        
                





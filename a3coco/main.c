#include <allegro5/allegro5.h>																					
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "cat.h"
#include "game.h"
#include "states.h"
#include "land.h"
#include "collision.h"

int main() {
        init_allegro();

        struct game *catland = create_game();
        if (!catland)
                return 1;

        set_allegro(catland);

        while (catland->state != EXIT) {
                al_wait_for_event(catland->queue, &catland->event);
                if (catland->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        catland->state = EXIT;

                if (catland->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                        catland->state = ESC;

                // isso aq e pra input
                if (catland->event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && catland->state == MENU)
                        input_menu(catland);

                if (catland->event.type == ALLEGRO_EVENT_KEY_DOWN && catland->state == PLAY)
                        switch (catland->event.keyboard.keycode) {
                                case ALLEGRO_KEY_A: 
                                        joystick_left_down(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_LCTRL: 
                                        joystick_crouch_down(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_D:
                                        joystick_right_down(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_SPACE:
                                        // se ele coletou o fish 2 tem direito a pular qts vezes quiser XD
                                        if (cat_alive(catland->player) && (cat_infinitejump(catland->land) || floor_collision(catland->player, catland->land))) {
                                                catland->player->vel_y = -VELOCITY;
                                                joystick_jump_down(catland->player->control);
                                        }
                                        break;
                                case ALLEGRO_KEY_LSHIFT:
                                        joystick_run_down(catland->player->control);
                                        break;
                                default:
                                        break; 
                        }
                
                if (catland->event.type == ALLEGRO_EVENT_KEY_UP && catland->state == PLAY)
                        switch (catland->event.keyboard.keycode) {
                                case ALLEGRO_KEY_A: 
                                        joystick_left_up(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_LCTRL: 
                                        joystick_crouch_up(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_D:
                                        joystick_right_up(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_SPACE:
                                        joystick_jump_up(catland->player->control);
                                        break;
                                case ALLEGRO_KEY_LSHIFT:
                                        joystick_run_up(catland->player->control);
                                        break;
                                default:
                                        break; 
                        }

                // isso aq eh pra renderizar (desenho)
                if (catland->event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(catland->queue)) {
                        al_clear_to_color(al_map_rgb(0,0,0));
                        switch (catland->state) {
                                case MENU:
                                        render_menu(catland);
                                        break;
                                case PLAY:
                                        render_play(catland);
                                        break;
                                /*
                                case WIN:
                                        render_win(catland);
                                        break;
                                case GAMEOVER:
                                        render_gameover(catland);
                                        break;
                                case ESC:
                                        render_esc(catland);
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
        
        
                





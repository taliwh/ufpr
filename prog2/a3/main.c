#include <allegro5/allegro5.h>																					
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "cat.h"
#include "game.h"
#include "states.h"
#include "land.h"

#include "physics.h"

int main() {
        //ai faz uma var  tipo init = init allegro e dps verifica if !init
        init_allegro();
        //fazer pro init retornar -1 se erro e verificar aq dai retornar 1 de erro ja q e main n esquecer
        struct game *catland = create_game();
        if (!catland)
                return 1;

        set_allegro(catland);

        while (catland->state != EXIT) {
                al_wait_for_event(catland->queue, &catland->event);
                apply_sounds(catland);
                if (catland->event.type == ALLEGRO_EVENT_MOUSE_AXES)
                        printf("x: %d y: %d\n", catland->event.mouse.x, catland->event.mouse.y);
                if (catland->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        catland->state = EXIT;

                if (catland->event.type == ALLEGRO_EVENT_KEY_DOWN && catland->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                        if (catland->state == PLAY) {
                                catland->state = PAUSE;
                                joystick_reset(catland->player->control);
                        }
                        else if (catland->state == PAUSE)
                                catland->state = PLAY;
                }

                // isso aq e pra input
                if (catland->state == MENU && catland->event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                        input_menu(catland);
                if ((catland->state == GAMEOVER || catland->state == WIN) && catland->event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                        input_gameover_win(catland);
                if (catland->state == PAUSE && catland->event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                        input_pause(catland);

                if (catland->state == PLAY && catland->event.type == ALLEGRO_EVENT_KEY_DOWN)
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
                                        apply_jump(catland);
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
                                case WIN:
                                        render_win(catland);
                                        break;
                                case GAMEOVER:
                                        render_gameover(catland);
                                        break;
                                case PAUSE:
                                        render_pause(catland);
                                        break;
                                default:
                                        break;
                        }                        							
    		        al_flip_display();							
		}
        }

        destroy_game(catland);
	return 0;
}
        
        
                





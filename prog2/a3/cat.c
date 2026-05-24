#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"

cat* create_cat(unsigned char side, enum face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y) {			

	if ((x - side/2 < 0) || (x + side/2 > max_x) || (y - side/2 < 0) || (y + side/2 > max_y)) 
                return NULL;												

	cat *player = (cat*) malloc(sizeof(cat));																								
	if (!player) 
                return NULL;	

	player->box.side = side;		
        player->box.face = LOOK_RIGHT; //inicialmente olha pra direita																																
	player->box.x = x;																																
	player->box.y = y;																																	
																																																				
	player->hp = 5;	

        player->control = joystick_create();		
        player->camera = create_camera();	
        player->sprites = put_catsprite();
        cat->frame = NORMAL;
        																											
	return player;																																	
}

void step_cat(cat *player, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y) {									

	if (!trajectory) 
                if ((player->box.x - steps*CAT_STEP) - player->box.side/2 >= 0) 
                        player->box.x = player->box.x - steps*CAT_STEP;

	else if (trajectory == 1) 
                if ((player->box.x + steps*CAT_STEP) + player->box.side/2 <= max_x) 
                        player->box.x = player->box.x + steps*CAT_STEP;

	else if (trajectory == 2) 
                if ((player->box.y - steps*CAT_STEP) - player->box.side/2 >= 0) 
                        player->box.y = player->box.y - steps*CAT_STEP;

	else if (trajectory == 3)
                if ((player->box.y + steps*CAT_STEP) + player->box.side/2 <= max_y) 
                        player->box.y = player->box.y + steps*CAT_STEP;

}

void destroy_cat(cat *player) {																																																								
	joystick_destroy(player->control);																												
	free(player);																																		
}



cat_kill
unsigned char cat_kill(struct enemy *animal, cat *player) {																																					

																																															
}



cat_frame

if cat crouch show image etc
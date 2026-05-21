#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"

cat box_create(unsigned char side, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){			

	if ((x - apothem < 0) || (x + apothem > max_x) || (y - apothem < 0) || (y + apothem > max_y)) 
                return NULL;												

	cat *new_cat = (cat) malloc(sizeof(cat));																								
	if (!new_cat) 
                return NULL;	
                																																										
	new_cat->side = side;																																																													
	new_cat->hp = 5;																																
	new_cat->x = x;																																
	new_cat->y = y;																																	
	new_cat->control = joystick_create();																											
        																											
	return new_cat;																																	
}

void cat_move(struct body *box , char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y){									

	if (!trajectory) { if ((box->x - steps*CAT_STEP) - box->apothem >= 0) box->x = box->x - steps*CAT_STEP;} 						
	else if (trajectory == 1){ if ((box->x + steps*CAT_STEP) + box->apothem <= max_x) box->x = box->x + steps*CAT_STEP;}			
	else if (trajectory == 2){ if ((box->y - steps*CAT_STEP) - box->apothem >= 0) box->y = box->y - steps*CAT_STEP;}				
	else if (trajectory == 3){ if ((box->y + steps*CAT_STEP) + box->apothem <= max_y) box->y = box->y + steps*CAT_STEP;}			
}

void cat_destroy(cat *box){																																																								
	joystick_destroy(box->control);																												
	free(box);																																		
}
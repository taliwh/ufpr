#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"

cat* create_cat(enum face face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y) {			
	if ((x < 0) || (x + SIDE > max_x) || (y < 0) || (y + SIDE > max_y)) 
                return NULL;												

	cat *player = (cat*) malloc(sizeof(cat));																								
	if (!player) 
                return NULL;	
		
        player->box.face = face;																													
	player->box.x = x + SIDE/2;																																
	player->box.y = y + SIDE/2;																																
																																																				
	player->hp = MAX_HP;	

        player->control = joystick_create();		
        player->camera = create_camera();	
        player->sprites = load_catsprite();
        player->frame = NORMAL;
        																											
	return player;																																	
}

struct sprite_cat* load_catsprite() {
        struct sprite_cat *sprites = malloc(sizeof(struct sprite_cat));
        if (!sprites)
                return NULL;

        sprites->normal = al_load_bitmap("assets/sprites/cat/normal.png");
        sprites->scared = al_load_bitmap("assets/sprites/cat/scared.png");
        sprites->crouch = al_load_bitmap("assets/sprites/cat/crouch.png");

        sprites->run = malloc(sizeof(ALLEGRO_BITMAP*) * RUN_SPRITE);
        sprites->jump = malloc(sizeof(ALLEGRO_BITMAP*) * JUMP_SPRITE);
        sprites->walk = malloc(sizeof(ALLEGRO_BITMAP*) * WALK_SPRITE);

        if (!sprites->walk || !sprites->run || !sprites->jump)
                return NULL;

        int i;
        for(i = 0; i < RUN_SPRITE; i++) {
                char path[100];
                sprintf(path, "assets/sprites/cat/run/%d.png", i+1);
                sprites->run[i] = al_load_bitmap(path);
        }

        for(i = 0; i < JUMP_SPRITE; i++) {
                char path[100];
                sprintf(path, "assets/sprites/cat/jump/%d.png", i+1);
                sprites->jump[i] = al_load_bitmap(path);
        }

        for(i = 0; i < WALK_SPRITE; i++)
        {
                char path[100];
                sprintf(path, "assets/sprites/cat/walk/%d.png", i+1);
                sprites->walk[i] = al_load_bitmap(path);
        }

        return sprites;
}

void step_cat(cat* player, char steps, unsigned char trajectory, unsigned short max_x, unsigned short max_y) {									
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

void destroy_catsprite(struct sprite_cat* sprites) {
        if (!sprites)
                return;

        al_destroy_bitmap(sprites->normal);
        al_destroy_bitmap(sprites->scared);
        al_destroy_bitmap(sprites->crouch);

        for (int i = 0; i < RUN_SPRITE; i++)
                al_destroy_bitmap(sprites->run[i]);

        for (int i = 0; i < JUMP_SPRITE; i++)
                al_destroy_bitmap(sprites->jump[i]);

        for (int i = 0; i < WALK_SPRITE; i++)
                al_destroy_bitmap(sprites->walk[i]);

        free(sprites->run);
        free(sprites->jump);
        free(sprites->walk);

        free(sprites);
}

void destroy_cat(cat *player) {	
        if (!player)
                return;

        destroy_camera(player->camera);
        destroy_catsprite(player->sprites);					        																																																		
	joystick_destroy(player->control);	

	free(player);
        

}

																																							
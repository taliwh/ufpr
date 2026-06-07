#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"
#include "camera.h"
#include "land.h"
#include "game.h"
#include "creatures.h"

cat* create_cat(enum face face, int x, int y, int max_x, int max_y) {			
	if (x + SIDE_CAT > max_x || y + SIDE_CAT > max_y) 
                return NULL;												

	cat *player = (cat*) malloc(sizeof(cat));																								
	if (!player) 
                return NULL;	
	
        player->box.face = face;
        player->box.side = SIDE_CAT;																													
	player->box.x = x + SIDE_CAT/2;																																
	player->box.y = y + SIDE_CAT/2;																																
	player->frame = NORMAL;																																																	
	player->hp = MAX_HP;	
        player->sprite_counter = 0;

        player->control = joystick_create();
        if (!player->control) {
                free(player);
                return NULL;
        }

        player->camera = create_camera();
        if (!player->camera) {
                joystick_destroy(player->control);
                free(player);
                return NULL;
        }

        player->sprites = load_catsprite();
        if (!player->sprites) {
                destroy_camera(player->camera);
                joystick_destroy(player->control);
                free(player);
                return NULL;
        }
																									
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

        if (!sprites->walk || !sprites->run || !sprites->jump) {
                free(sprites->run);
                free(sprites->jump);
                free(sprites->walk);

                al_destroy_bitmap(sprites->normal);
                al_destroy_bitmap(sprites->scared);
                al_destroy_bitmap(sprites->crouch);

                free(sprites);
                return NULL;
        }

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

void step_cat(cat* player, int speed, unsigned char trajectory, int max_x, int max_y) {									
	if (!trajectory) {
                if ((player->box.x - speed) - player->box.side/2 >= 0) 
                        player->box.x -= speed;

        } else if (trajectory == 1) { 
                if ((player->box.x + speed) + player->box.side/2 <= max_x) 
                        player->box.x += speed;

        } else if (trajectory == 2) { 
                if ((player->box.y - speed) - player->box.side/2 >= 0) 
                        player->box.y -= speed;

        } else if (trajectory == 3) {
                if ((player->box.y + speed) + player->box.side/2 <= max_y) 
                        player->box.y += speed;
        }
}

void update_position (cat* player) {
        if (!player)
                return;

        int speed = CAT_STEP;

        if (player->control->run)
                speed = 20;

        if (player->control->crouch)
                speed = 5;

        if (player->control->left && !player->control->right) {
                player->box.face = LOOK_LEFT;
                step_cat(player, speed, 0, LAND_WIDTH, Y_SCREEN);
        }
        
        if (player->control->right && !player->control->left) {
                player->box.face = LOOK_RIGHT;
                step_cat(player, speed, 1, LAND_WIDTH, Y_SCREEN);
        }

}

void apply_gravity(cat *player) {
        if (!player)
                return;

        if (player->control->jump && player->box.y > 130) {
                player->box.y -= 15;  // sobe
        } else {
                player->control->jump = 0;
                player->box.y += GRAVITY;
        }
        
}

int cat_chao (cat *player, world *land) {
        if (!player || !land)
                return -1;

        int no_chao = 0;
        int foot = player->box.y + player->box.side/2;

        for (int i = 0; i < NUM_SOLIDS; i++) {
                struct solid s = land->solids[i];
                if (!player->control->jump && 
                player->box.x >= s.x &&
                player->box.x <= s.x + s.width &&
                abs(foot - s.y) <= 10) {
                        no_chao = 1;
                }
        }

        return no_chao;
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

																																							
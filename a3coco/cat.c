#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"
#include "camera.h"
#include "land.h"
#include "game.h"
#include "creatures.h"
#include "collision.h"

cat* create_cat(enum face face, int x, int y, int max_x, int max_y) {			
	if (x + SIDE_CAT > max_x || y + SIDE_CAT > max_y) 
                return NULL;												

	cat *player = calloc(1, sizeof(cat));																								
	if (!player) 
                return NULL;	
	
        player->box.face = face;
        player->box.side = SIDE_CAT;																													
	player->box.x = x + SIDE_CAT/2;																																
	player->box.y = y + SIDE_CAT/2;																																
	player->frame = NORMAL;																																																	
	player->hp = MAX_HP;	

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

void step_cat(cat* player, int speed, unsigned char trajectory, int max_x) {
        if (!player)
                return;					

	if (!trajectory) {
                if ((player->box.x - speed) - player->box.side/2 >= 0) 
                        player->box.x -= speed;
        }

        else if (trajectory) {
                if ((player->box.x + speed) + player->box.side/2 <= max_x) 
                        player->box.x += speed;
        }       
}

void update_position (cat* player, world *land) {
        if (!player)
                return;

        int speed = CAT_STEP;

        if (player->control->run)
                speed = 25;

        if (player->control->crouch)
                speed = 5;

        if (player->control->left && !player->control->right) {
                player->box.face = LOOK_LEFT;
                step_cat(player, speed, 0, LAND_WIDTH);
        }
        if (player->control->right && !player->control->left) {
                player->box.face = LOOK_RIGHT;
                step_cat(player, speed, 1, LAND_WIDTH);
        }
        int vale;
        //aplica colisao com parede se o gato caiu
        if (!floor_collision(player, land)) {

                if (player->box.x < land->solids[3].x)
                        vale = 1;
                else if (player->box.x < land->solids[5].x)
                        vale = 2;
                else 
                        vale = 3;
                wall_collision(player, land, vale);
        }
}

void update_frame(cat *player) {
        if (!player)
                return;
        
        // define qual animação deve estar ativa
        if (player->control->crouch)
                player->frame = DOWN;

        else if (player->control->jump)
                player->frame = JUMP;

        else if (player->control->run && (player->control->left || player->control->right))
                player->frame = RUN;

        else if (player->control->left || player->control->right)
                player->frame = WALK;

        else
                player->frame = NORMAL; 
}

void apply_gravity(cat *player, world *land) { 
        if (!player || !land)       
                return; 
        player->old_y = player->box.y; 
        player->vel_y += GRAVITY; 
        player->box.y += player->vel_y;

        floor_collision(player, land);
}
//funcao pra ver se ele coletou o fish
//funcao pra ver se ele ta morto
//botar na main dai, pq ele so pode pular se tiver vivo

//void cat_hp
int cat_alive(cat *player) {
        if (!player)
                return -1;
        if (player->hp == 0)
                return 0;

        return 1;
}

int cat_infinitejump(world *land) {
        if (!land)
                return -1;
        if (land->fish2->collected)
                return 1;
        return 0;
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

																																							
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"
#include "camera.h"
#include "land.h"
#include "creatures.h"
#include "physics.h"

cat* create_cat(enum face face, int x, int y, int max_x, int max_y) {			
	if (x + SIDE > max_x || y + SIDE > max_y) 
                return NULL;												

	cat *player = calloc(1, sizeof(cat));																								
	if (!player) 
                return NULL;	
	
        player->box.face = face;																												
	player->box.x = x + SIDE/2;																																
	player->box.y = y + SIDE/2;																																
	player->frame = NORMAL;																																																	
	player->hp = MAX_HP;	
        player->chao = 1;

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

int cat_win(cat *player) {
        if (!player)
                return -1;
        if (player->box.x >= 3663)
                return 1;
        return 0;
}


void update_position (cat* player, world *land) {
        if (!player)
                return;

        int speed = CAT_STEP;

        if (player->control->run)
                speed = 20;

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

        //colisoes q afetam a posicao
        wall_collision(player, land);
        floor_collision(player, land);
        //if not live 

}
void update_hp(cat *player, world *land) {
        if (!player || !land)
                return;
        int instakill = 0;

        if (player->cooldown.damage_timer > 0) {
                player->cooldown.damage_timer--;
                return;
        }

        if (player->cooldown.death_timer > 0) {
                player->cooldown.death_timer--;
                return;
        }

        if (hazard_collision(player, land, &instakill)) {
                if (instakill) {
                        player->hp = 0;
                        player->cooldown.death_timer = 20;
                        player->cooldown.just_died = 1;
                }
                else {
                        player->hp--;
                        player->cooldown.damage_timer = 20;
                        if (cat_alive(player))
                                player->cooldown.took_damage = 1;
                        else
                                player->cooldown.just_died = 1;
                        
                }
        }

        if (entity_collision(player->box, land->fox1->box) || entity_collision(player->box, land->fox2->box) || (entity_collision(player->box, land->bird->box) && !player->control->crouch)) {
                player->hp--;
                player->cooldown.damage_timer = 20;
                if (cat_alive(player))
                        player->cooldown.took_damage = 1;
                else 
                        player->cooldown.just_died = 1;
                
        }
        
        if (fish1_taken(player,land) || fish2_taken(player, land)) {
                player->hp += 1; 
                player->cooldown.took_fish = 1;
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

void step_cat (cat* player, int speed, unsigned char trajectory, int max_x) {									
	if (!trajectory) {
                if ((player->box.x - speed) - SIDE/2 >= 0) 
                        player->box.x -= speed;
        }

        else if (trajectory == 1) {
                if ((player->box.x + speed) + SIDE/2 <= max_x) 
                        player->box.x += speed;
        }
}

int cat_onground (cat *player) {
        if (!player)
                return -1;
        if (player->chao)
                return 1;

        return 0;
}

int cat_alive (cat *player) {
        if (!player)
                return -1;
        if (player->hp == 0)
                return 0;
        return 1;
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

																																							
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "creatures.h"
#include "cat.h"
#include "land.h"

fish* create_fish (int x, int y, char fish_type) {
        fish *pexe = malloc(sizeof(fish));
        if (!pexe)
                return NULL;

        pexe->collected = 0;

        if (fish_type == 1) 
                pexe->sprite = al_load_bitmap("assets/sprites/fish/Clownfish.png");

        if (fish_type == 2) 
                pexe->sprite = al_load_bitmap("assets/sprites/fish/Surgeonfish.png");
        
        pexe->box.face = LOOK_LEFT;
        pexe->box.side = SIDE_FISH;
        pexe->box.x = x + SIDE_FISH/2;
        pexe->box.y = y + SIDE_FISH/2;

        return pexe;
}

enemy* create_fox (int x, int y, int end) {
        enemy* fox = malloc(sizeof(enemy));
        if (!fox)
                return NULL;

        fox->sprites = load_foxsprite();

        fox->box.face = LOOK_LEFT;
        fox->box.side = SIDE_FOX;
        fox->box.x = x + SIDE_FOX/2;
        fox->box.y = y + SIDE_FOX/2;
        fox->sprite_counter = 0;
        fox->start_x = x + SIDE_FOX/2;
        fox->vel_x = 0;

        fox->end_x = end;

        return fox;
}

ALLEGRO_BITMAP** load_foxsprite () {
        ALLEGRO_BITMAP** sprites = malloc(sizeof(ALLEGRO_BITMAP*) * FOX_SPRITE);
        if (!sprites) 
                return NULL;

        for(int i = 0; i < FOX_SPRITE; i++) {
                char path[100];
                sprintf(path, "assets/sprites/fox/%d.png", i+1);
                sprites[i] = al_load_bitmap(path);
        }

        return sprites;
}

enemy* create_bird (int x, int y, int end) {
        enemy* bird = malloc(sizeof(enemy));
        if (!bird)
                return NULL;

        bird->sprites = load_birdsprite();
        bird->box.face = LOOK_LEFT;
        bird->box.side = SIDE_BIRD;
        bird->box.x = x + SIDE_BIRD/2;
        bird->box.y = y + SIDE_BIRD/2;
        bird->end_x = end;

        return bird;
}

ALLEGRO_BITMAP** load_birdsprite () {
        ALLEGRO_BITMAP** sprites = malloc(sizeof(ALLEGRO_BITMAP*) * BIRD_SPRITE);
        if (!sprites) 
                return NULL;

        for(int i = 0; i < BIRD_SPRITE; i++) {
                char path[100];
                sprintf(path, "assets/sprites/bird/%d.png", i+1);
                sprites[i] = al_load_bitmap(path);
        }

        return sprites;
}

void update_fox(enemy *fox) {
        if (!fox) 
                return;

        fox->box.x += fox->vel_x;

        if (fox->vel_x > 0)
                fox->box.face = LOOK_RIGHT;
        else
                fox->box.face = LOOK_LEFT;

        if (fox->box.x >= fox->end_x)
                fox->vel_x = -FOX_SPEED;

        if (fox->box.x <= fox->start_x)
                fox->vel_x = FOX_SPEED;


}

void update_bird(enemy *bird) {
        if (!bird)
                return;

        bird->box.x += bird->vel_x;

        if (bird->vel_x > 0)
                bird->box.face = LOOK_RIGHT;
        else
                bird->box.face = LOOK_LEFT;

        if (bird->box.x >= bird->end_x)
                bird->vel_x = -FOX_SPEED;

        if (bird->box.x <= bird->start_x)
                bird->vel_x = FOX_SPEED;
}

void draw_fox (enemy *fox, int cam) {
        if (!fox)
                return;

        fox->sprite_counter++;

        if (fox->sprite_counter >= FOX_SPRITE * 5)
                fox->sprite_counter = 0;

        ALLEGRO_BITMAP *fox_sprite =
                fox->sprites[fox->sprite_counter / 5];

        int fox_flip = 0;

        if (fox->box.face == LOOK_LEFT)
                fox_flip = ALLEGRO_FLIP_HORIZONTAL;

        al_draw_scaled_bitmap(
                fox_sprite,
                0, 0,
                al_get_bitmap_width(fox_sprite),
                al_get_bitmap_height(fox_sprite),
                (fox->box.x - SIDE_FOX/2) - cam,
                fox->box.y - SIDE_FOX/2,
                64, 64,
                fox_flip
        );

        fox->sprite_counter++;
}

void destroy_fish (fish *pexe) {
        if (!pexe)
                return;

        al_destroy_bitmap(pexe->sprite);
        free(pexe);
}

void destroy_foxsprite (ALLEGRO_BITMAP **sprites) {
    if (!sprites)
        return;

    for (int i = 0; i < 4; i++)
        al_destroy_bitmap(sprites[i]);
    free(sprites);
}

void destroy_birdsprite (ALLEGRO_BITMAP **sprites) {
    if (!sprites)
        return;

    for (int i = 0; i < 6; i++)
        al_destroy_bitmap(sprites[i]);
    free(sprites);
}

void destroy_fox (enemy *fox) {
    if (!fox)
        return;

    destroy_foxsprite(fox->sprites);
    free(fox);
}

void destroy_bird (enemy *bird) {
    if (!bird)
        return;

    destroy_birdsprite(bird->sprites);
    free(bird);
}

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "creatures.h"

fish* create_fish (unsigned short x, unsigned short y) {
        fish *pexe = malloc(sizeof(fish));
        if (!pexe)
                return NULL;
        
        pexe->sprite = al_load_bitmap("assets/sprites/fish/Clownfish.png");

        pexe->box.face = LOOK_LEFT;
        pexe->box.side = SIDE_FISH;
        pexe->box.x = x + SIDE_FISH/2;
        pexe->box.y = y + SIDE_FISH/2;
        
        pexe->collected = 0;

        return pexe;
}

enemy* create_fox (unsigned short x, unsigned short y, unsigned short end) {
        enemy* fox = malloc(sizeof(enemy));
        if (!fox)
                return NULL;

        fox->sprites = load_foxsprite();

        fox->box.face = LOOK_LEFT;
        fox->box.side = SIDE_FOX;
        fox->box.x = x + SIDE_FOX/2;
        fox->box.y = y + SIDE_FOX/2;
        
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

enemy* create_bird (unsigned short x, unsigned short y, unsigned short end) {
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

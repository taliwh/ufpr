#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "creatures.h"

fish* create_fish (int x, int y, char fish_type) {
        fish *pexe = malloc(sizeof(fish));
        if (!pexe)
                return NULL;

        pexe->collected = 0; // inicialmente nao ha coleta de peixes

        pexe->box.x = x + SIDE/2;
        pexe->box.y = y + SIDE/2;
        pexe->box.face = LOOK_LEFT;

        // verifica qual tipo de peixe deve ser renderizado
        if (fish_type == 1) 
                pexe->sprite = al_load_bitmap("assets/sprites/fish/Clownfish.png");

        if (fish_type == 2) 
                pexe->sprite = al_load_bitmap("assets/sprites/fish/Surgeonfish.png");

        return pexe;
}

enemy* create_fox (int x, int y, int end) {
        enemy* fox = malloc(sizeof(enemy));
        if (!fox)
                return NULL;

        fox->box.x = x + SIDE/2;
        fox->box.y = y + SIDE/2;
        fox->box.face = LOOK_LEFT;

        fox->start_x = x + SIDE/2;
        fox->end_x = end;
        fox->vel_x = FOX_SPEED;

        fox->sprite_counter = 0;
        fox->sprites = load_foxsprite();

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

        bird->box.x = x + SIDE/2;
        bird->box.y = y + SIDE/2;
        bird->box.face = LOOK_LEFT;

        bird->start_x = x + SIDE/2;  
        bird->end_x = end;
        bird->vel_x = BIRD_SPEED;    

        bird->sprite_counter = 0;         
        bird->sprites = load_birdsprite();

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

        // atualiza sua direcao
        if (fox->vel_x > 0)
                fox->box.face = LOOK_RIGHT;
        else
                fox->box.face = LOOK_LEFT;

        // abs garante a direcao correta mesmo se a raposa ultrapassar o limite
        if (fox->box.x >= fox->end_x)
                fox->vel_x = -abs(fox->vel_x);
 
        if (fox->box.x <= fox->start_x)
                fox->vel_x = abs(fox->vel_x);
}

void update_bird(enemy *bird) {
        if (!bird)
                return;

        bird->box.x += bird->vel_x;

        // atualiza sua direcao
        if (bird->vel_x > 0)
                bird->box.face = LOOK_RIGHT;
        else
                bird->box.face = LOOK_LEFT;

        // abs garante a direcao correta mesmo se a ave ultrapassar o limite
        if (bird->box.x >= bird->end_x)
                bird->vel_x = -abs(bird->vel_x);
 
        if (bird->box.x <= bird->start_x)
                bird->vel_x = abs(bird->vel_x);
}


void draw_bird (enemy *bird, int cam) {
        if (!bird)
                return;

        bird->sprite_counter++;

        // reinicia o ciclo de animacao ao chegar no ultimo frame
        if (bird->sprite_counter >= BIRD_SPRITE * 5)
                bird->sprite_counter = 0;

        // cada sprite dura 5 frames (contador / 5 = indice do sprite)
        ALLEGRO_BITMAP *bird_sprite =
                bird->sprites[bird->sprite_counter / 5];

        int bird_flip = 0;

        // arruma a direcao da sprite
        if (bird->box.face == LOOK_LEFT)
                bird_flip = ALLEGRO_FLIP_HORIZONTAL;

        al_draw_scaled_bitmap(bird_sprite, 0, 0, al_get_bitmap_width(bird_sprite),
                al_get_bitmap_height(bird_sprite),
                (bird->box.x - SIDE/2) - cam,
                bird->box.y - SIDE/2,
                100, 100,
                bird_flip
        );
}

void draw_fox (enemy *fox, int cam) {
        if (!fox)
                return;

        fox->sprite_counter++;

        // reinicia o ciclo de animacao ao chegar no ultimo frame
        if (fox->sprite_counter >= FOX_SPRITE * 5)
                fox->sprite_counter = 0;
                
        // cada sprite dura 5 frames (contador / 5 = indice do sprite)
        ALLEGRO_BITMAP *fox_sprite =
                fox->sprites[fox->sprite_counter / 5];

        int fox_flip = 0;

        // arruma a direcao da sprite
        if (fox->box.face == LOOK_LEFT)
                fox_flip = ALLEGRO_FLIP_HORIZONTAL;

        al_draw_scaled_bitmap(
                fox_sprite,
                0, 0,
                al_get_bitmap_width(fox_sprite),
                al_get_bitmap_height(fox_sprite),
                (fox->box.x - SIDE/2) - cam,
                fox->box.y - SIDE/2,
                64, 64,
                fox_flip
        );

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

// joystick.c/joystick.h : arquivos adaptados do jogo agressive squares do prof vinicius fulber, mecanicas sem o uso de XOR 

#include <stdlib.h>
#include "joystick.h"

joystick* joystick_create() {
        joystick *element = malloc(sizeof(joystick));

        if (!element)
                return NULL;

        element->right = 0;
        element->left = 0;
        element->up = 0;
        element->down = 0;
        element->jump = 0;
        element->crouch = 0;
        element->run = 0;

        return element;
}

void joystick_destroy(joystick *element) {
        free(element);
}

void joystick_left_down(joystick *element) {
        element->left = 1;
}

void joystick_left_up(joystick *element) {
        element->left = 0;
}

void joystick_right_down(joystick *element) {
        element->right = 1;
}

void joystick_right_up(joystick *element) {
        element->right = 0;
}

void joystick_down_down(joystick *element) {
        element->down = 1;
}

void joystick_down_up(joystick *element) {
        element->down = 0;
}

void joystick_jump_down(joystick *element) {
        element->jump = 1;
}

void joystick_jump_up(joystick *element) {
        element->jump = 0;
}

void joystick_crouch_down(joystick *element) {
        element->crouch = 1;
}

void joystick_crouch_up(joystick *element) {
        element->crouch = 0;
}

void joystick_run_down(joystick *element) {
        element->run = 1;
}

void joystick_run_up(joystick *element) {
        element->run = 0;
}

void joystick_reset(joystick *element) {
        element->right  = 0;
        element->left   = 0;
        element->up     = 0;
        element->down   = 0;
        element->jump   = 0;
        element->crouch = 0;
        element->run    = 0;
}
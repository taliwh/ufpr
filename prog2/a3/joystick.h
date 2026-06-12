// joystick.c/joystick.h : arquivos adaptados do jogo agressive squares do prof vinicius fulber, mecanicas sem o uso de XOR 

#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct {
    unsigned char right;
    unsigned char left;
    unsigned char up;
    unsigned char down;
    unsigned char jump;
    unsigned char crouch;
    unsigned char run;
} joystick;

joystick* joystick_create();
void joystick_destroy(joystick *element);

void joystick_left_down(joystick *element);
void joystick_left_up(joystick *element);

void joystick_right_down(joystick *element);
void joystick_right_up(joystick *element);

void joystick_down_down(joystick *element);
void joystick_down_up(joystick *element);

void joystick_jump_down(joystick *element);
void joystick_jump_up(joystick *element);

void joystick_crouch_down(joystick *element);
void joystick_crouch_up(joystick *element);

void joystick_run_down(joystick *element);
void joystick_run_up(joystick *element);

void joystick_reset(joystick *element);
#endif


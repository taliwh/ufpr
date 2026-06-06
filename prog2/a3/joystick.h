#ifndef __JOYSTICK__ 																												
#define __JOYSTICK__																												

typedef struct {																													
	unsigned char right;																											
	unsigned char left;																												
	unsigned char up;																												
	unsigned char down;																																																					//Botão de movimentação para baixo 
	unsigned char jump;
        unsigned char crouch;
        unsigned char run;
} joystick;																														

joystick* joystick_create();																										
void joystick_destroy(joystick *element);																							
void joystick_right(joystick *element);																								
void joystick_left(joystick *element);																								
void joystick_up(joystick *element);																							
void joystick_down(joystick *element);																							
void joystick_jump(joystick *element);
void joystick_crouch(joystick *element);
void joystick_run(joystick *element);																						

#endif																															
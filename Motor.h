#ifndef __MOTOR_H_
#define __MOTOR_H_

#include <avr/io.h>
#include "RoboCAR.h"

/*
   PA0:

*/

#define OCR_val(duty)	((unsigned short)(duty*10.23))


#define FORWARD      0x05
#define BACKWARD     0x0A
#define STOP		 0x00
#define RIGHT_CTRL   0x20
#define LEFT_CTRL    0x40

void MOTOR_Init();
void Backward();
void Backward_left();
void Backward_right();
void Forward();
void Forward_left();
void Forward_right();
void Stop();
void Left_turn();
void Right_turn();
void PWM_update(char motor, unsigned char duty);
void Speed_up();
void Speed_down();
void PWM_update_left(unsigned char duty);
void PWM_update_right(unsigned char duty);

enum {
LEFT_M,
RIGHT_M,
ALL
};

#endif



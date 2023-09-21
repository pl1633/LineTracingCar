#ifndef __PSD_H_
#define __PSD_H_

#include <avr/io.h>
#include "RoboCAR.h"


void PSD_Init();
unsigned int ADC_Convert(unsigned char ch);
unsigned int Get_dist_cm();

void send_dist_msg(unsigned int dist);

 

#endif

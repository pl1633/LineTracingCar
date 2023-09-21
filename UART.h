#ifndef __UART_H_
#define __UART_H_

#include <avr/io.h>
#include "RINGBUFFER.h"
#include "RoboCAR.h"

void UART_Init();
void UART_putch(unsigned char data);
void UART_getch();
void UART_putstr(char *data);




#endif

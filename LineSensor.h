#ifndef __LINE_H_
#define __LINE_H_

#include <avr/io.h>
#include "RoboCAR.h"




#define ADC2VOUT	((256*2.56)/1024*5) // 0.128
#define CLK			0x02
#define Din			0x04
#define SYNC		0x01
#define DAC_PORT	PORTG
#define	DAC_DDR		DDRG

void LineSensor_Init();
void Convert_sDAC(unsigned char tmp);
void Hex2Bin_UART_OUT(unsigned char hexdeci);


#endif

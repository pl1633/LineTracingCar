#include "PSD.h"
#include "UART.h"

#include <stdio.h>
/*
    PA0~3   : motor direction

	PB2		: F LED
	PB3		: B LED
	PB5		: R Motor En(PWM)
	PB6		: L Motor En(PWM)

	PD2~3	: UART1 Rx Tx

	PE0~1	: UART0 Rx, Tx
	PE2		: buzzer
	PF0		: PSD sensor Input
*/
u16 PSD_val[14] = {745,512,397,331,283,255,224,200,188,171,164,151,116,110};
u08 PSD_cm[14] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75};



void PSD_Init()
{
  DDRF = 0x00; 
  PORTF = 0x00;
}

u16 ADC_Convert(unsigned char ch)
{
  u16 ret = 0;
  ADMUX = 0xc0 | ch; //Ref 2.56v 
  ADCSR = 0xa7; // 128 prescaler
  ADCSR |= 0x40; //ADC start conversion

  while((ADCSR&0x10)==0x00);

  ADCSR |= 0x10;

  ret = ADCL & 0xff;
  ret |= ADCH << 8;
  ADMUX = 0x0; // init ADC
  ADCSR = 0x0; // init ADC

  return ret;

}

u16 Get_dist_cm()
{
  u08 i,j;
  u16 tmp_val;
  u08 tmp_cm;
  u08 tmp;

  int value = ADC_Convert(0x00); // Select ADC 0 channel
  int dist = 0;

  for(i=0,j=0;i<14;i++)
  {
    if(value<PSD_val[i])
	  j=i;
    else
	  break;
   }
   tmp_cm = PSD_cm[i] - PSD_cm[j];
   tmp_val = PSD_val[j]-PSD_val[i];

   tmp = tmp_val/tmp_cm;
   dist = ((PSD_val[j]-value)/tmp)+PSD_cm[j];


   return dist;
}

void send_dist_msg(u16 dist)
{
  char msg[20];
  sprintf(msg,"dist = %d\r\n",dist);
  UART_putstr(msg);

}

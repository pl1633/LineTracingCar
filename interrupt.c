#include "Interrupt.h"

volatile unsigned int count = 0;
extern unsigned int psd_dist;
extern unsigned char lineValue;

char psd_msg[40];


ISR(TIMER0_OVF_vect)// 1ms timer
{
  //static unsigned int flag = 0;
  TCNT0 = 6;

  if(count == 200) // 200ms timer
  {
    sprintf(psd_msg, "obstacle = %d(cm),\r\n", psd_dist); // Check PSD Sensor Value to -> (cm)
    UART_putstr(psd_msg);                                 // (cm) UART OUT

	Hex2Bin_UART_OUT(lineValue); // for line sensor ( line sensor u08 value -> to binary UART out)

	
    count = 0;
  }


  count++;
}


void Timer0_Init()
{
  TCCR0 |= 0x04;
  TCNT0 |= 6;
  TIMSK |= 0x01;
  sei();
  UART_putstr("Timer0 Init - ok \r\n");

}

void Timer1_PWM_Init()
{
  TCCR1A |= 0xA3;
  TCCR1B |= 0x02;
  TCCR1C |= 0x00;
  TCNT1 |= 0x0000;
  OCR1A = 0x3FF;
  OCR1B = 0x3FF;

  UART_putstr("Timer1_PWM Init - ok \r\n");
}


#include "LED.h"


unsigned char led_flag = 0;

void Front_LED_on()
{
  PORTB |= 0x04;
}
void Front_LED_off()
{
  PORTB &= ~0x04;
}
void Rear_LED_on()
{
   PORTB |= 0x08;
}
void Rear_LED_off()
{
   PORTB &= ~0x08;
}
void LED_Init()
{
  DDRB = 0xFF;
  UART_putstr("LED Init - ok \r\n");
  
}

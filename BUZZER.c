#include "BUZZER.h"

unsigned char buzzer_flag = 0;

void BUZZER_Init()
{
  DDRE |= 0x04;
  PORTE &= ~0x04;
  UART_putstr("BUZZER Init - ok \r\n");
}
void Buzzer_on()
{
  PORTE |= 0x04;
}
void Buzzer_off()
{
  PORTE &= ~0x04;
}



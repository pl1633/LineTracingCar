#include "UART.h"


void UART_Init()
{
  DDRD = 0xFB; //RX(입력 0), Tx(출력,1)
  UCSR1B = 0x18; // RX,TX Enable
  UCSR1C = 0x06; // 비동기 방식, No Parity, 1 Stop bit
  UBRR1H = 0x00;
  UBRR1L = 0x03; // 7.3728MHz 에서의 115200bps

  UART_putstr("UART Init - ok \r\n");
}

void UART_putch(unsigned char data)
{
  while((UCSR1A & 0x20) == 0)
  {
  } 
  UDR1 = data;
   
}

void UART_getch()
{
  unsigned char data;

  while(1)
  {
	 if(UCSR1A & 0x80)
     {
       data = UDR1;
	   RingBuff_Put(&ring, data);
     }
	 else
	 {
	   break;
	 }
  }
 
}

void UART_putstr(char *data)
{
  while(*data != '\0')
  {
    UART_putch(*data);
	data++;
  }
}

#include "LineSensor.h"


char line_msg[40];

void LineSensor_Init()
{
  DDRF = 0x00;
  PORTF = 0x00;
  DDRG = 0xff;

  u16 infr[4] = {0};

  Convert_sDAC(0);

  infr[0] = ADC_Convert(4);
  infr[1] = ADC_Convert(5);
  infr[2] = ADC_Convert(6);
  infr[3] = ADC_Convert(7);

  u08 i;
  u16 ADC_max = infr[0];
  u16 ADC_min = infr[0];
  u16 ADC_mid = 0;
  u16 V_ref = 0;

  for(i=0;i<4;i++)
  {
    if(infr[i]>=ADC_max)
	{
	  ADC_max = infr[i];
	}
	if(infr[i]<=ADC_min)
	{
	  ADC_min = infr[i];
	}
  }

  sprintf(line_msg, "ADC_max = %04x,\r\n", ADC_max);
  UART_putstr(line_msg);

  sprintf(line_msg, "ADC_min = %04x,\r\n", ADC_min);
  UART_putstr(line_msg);

  ADC_mid = (ADC_max + ADC_min)/2;

  sprintf(line_msg, "ADC_mid = %04x,\r\n", ADC_mid);
  UART_putstr(line_msg);

  V_ref = (u08)(ADC_mid*ADC2VOUT);
  sprintf(line_msg, "LineSensor_Init, V_ref = %02x,\r\n", V_ref);
  UART_putstr(line_msg);

  // Sensor Value is Not Exact
  V_ref = 0x01; // find proper value!!!!(0x01 ~ 0x02 ? )
  Convert_sDAC(V_ref);
  
  _delay_ms(20);

}

void Convert_sDAC(unsigned char tmp)
{
  u16 data = 0;
  u16 mask= 0x8000;
  u08 i;
  data |= tmp << 4;

  DAC_PORT |= SYNC;
  _delay_ms(1);
  DAC_PORT |= (CLK);
  _delay_ms(1);
  DAC_PORT &= ~(CLK);
  _delay_ms(1);
  DAC_PORT &= ~SYNC;
  _delay_ms(1);

  for(i=0;i<16;i++)
  {
    DAC_PORT |= CLK;
	_delay_ms(1);

	if(data & mask)
	{
	  DAC_PORT |= Din;
	}
	else
	{
	  DAC_PORT &= ~Din;
	}

	_delay_ms(1);
	DAC_PORT &= ~CLK;
	_delay_ms(1);
	data = data << 1;
  }

}

void Hex2Bin_UART_OUT(unsigned char hexdeci)
{
  u08 i = 0;
  for(i=0;i<8;i++)
  {
	  if(hexdeci & 0x80)
	  {
	    UART_putch('1');
	  }
	  else
	  {
        UART_putch('0');
	  }
	  
	  hexdeci = hexdeci<<1;
  }
  UART_putch('\r');
  UART_putch('\n');
}

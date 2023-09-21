#include "Motor.h"


#include <stdio.h>

u08 g_duty_per = 100;
u08 turn_flag = 0;

void MOTOR_Init()
{
  DDRB |= 0x60; // PB5: right motor Enable,  PB6: left motor Enable
  PORTB |= 0x60;
  DDRA |= 0x0F; // PA0~3: motor direction
  UART_putstr("MOTOR Init - ok \r\n");

}

void Forward()
{
  PORTA = 0b00000110;
}
void Left_turn()
{
  PORTA = 0b00001010;
}
void Right_turn()
{
  PORTA = 0b00000101;
}
void Forward_left()
{
  PORTA = 0b00000010;
}
void Forward_right()
{
  PORTA = 0b00000100;
}
void Backward()
{
  PORTA = 0b00001001;
}
void Backward_left()
{
  PORTA = 0b00000001;
}
void Backward_right()
{
  PORTA = 0b00001000;
}
void Stop()
{
  PORTA &= ~0x0F;
}

void PWM_update(char motor, u08 duty)
{
  unsigned short val = OCR_val(duty);

  switch(motor)
  {
    case LEFT_M:
	OCR1B = val;
	break;

	case RIGHT_M:
	OCR1A = val;
	break;

	case ALL:
	OCR1B = val;
	OCR1A = val;
	break;
  }

}

void Speed_up()
{
  char msg[40];
  
  if(g_duty_per >=0 && g_duty_per <=90)
  {
    g_duty_per += 10;
	PWM_update(ALL, g_duty_per);
	sprintf(msg, "DUTY = %d,\r\n", g_duty_per);
	UART_putstr(msg);

  }
  else
  {
    sprintf(msg, "DUTY = %d,\r\n", g_duty_per);
    UART_putstr(msg);
  }
 
}

void Speed_down()
{
  char msg[40];

  if(g_duty_per >= 10 && g_duty_per <=100)
  {
    g_duty_per -= 10;
	PWM_update(ALL, g_duty_per);
	sprintf(msg, "DUTY = %d,\r\n", g_duty_per);
    UART_putstr(msg);
  }
  else
  {
    sprintf(msg, "DUTY = %d,\r\n", g_duty_per);
	UART_putstr(msg);
  }

}


void PWM_update_left (u08 duty)
{
  unsigned short val = OCR_val(duty);
	OCR1B = val;


  }
  void PWM_update_right (u08 duty)
{
  unsigned short val = OCR_val(duty);
	OCR1A = val;

  }




#include "RoboCAR.h"


unsigned int psd_dist = 0;
unsigned char lineValue;

int main(void)
{ 
	unsigned char rcv_data;
	
	UART_Init();
	BUZZER_Init();
	LED_Init();
	Timer1_PWM_Init();
	Timer0_Init();
	MOTOR_Init();
	PSD_Init();
	LineSensor_Init();


   while(1)
   {
     rcv_data = RingBuff_Get(&ring);
	 psd_dist = Get_dist_cm();     // 거리값을 받는다.
	 lineValue = PINC;  //라인센서값을 받는다.
	 Hex2Bin_UART_OUT(lineValue);  //라인센서값 컴퓨터로 출력
	 void send_dist_msg(psd_dist); //거리값 컴퓨터로 출력
	 if(psd_dist < 20){ Stop();}  //앞에 장애물 있으면 정지


	 switch(lineValue)
	 {
	   
	   case 11100110: 	Forward();
	   case 11101110: 	Forward();		  		  
	   case 11110110: 	Forward();	
	   break;
	   
	//우측센서 라인 보정 ***************************************
	case 01110010 : Forward_right();
	case 01111010 : Forward_right();
	case 01111000 : Forward_right();
	case 01111100 : Forward_right();
	case 01111100 : Forward_right();
	case 01111110:  Forward_right();
	break;

	//좌측센서 라인 보정 ***************************************
	case 01100110 : PWM_update_left (u08 duty)
	case 01101110 : PWM_update_left (u08 duty)
	case 01001110 : PWM_update_left (u08 duty)
	case 01011110 : PWM_update_left (u08 duty)
	case 00011110 : PWM_update_left (u08 duty)
	break;

	 }

   }
   return 0;
}


#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "pwm.h"

int main(void)	
{
	u16 servo_pwm;	
	delay_init(72);
	TIM2_PWM_Init(2000, 719);	//100Khz�ļ���Ƶ�ʣ�������2000Ϊ20ms   

	while(1)
	{
		for(servo_pwm = 0; servo_pwm < 300; servo_pwm++) 									 
		{	    
			TIM_SetCompare3(TIM2, servo_pwm);
			delay_ms(20);					 //��ʱ��ú���Ҫ���Լ�һ����ԡ�
		}
		for(servo_pwm = 300; servo_pwm > 0; servo_pwm--) 									 
		{
			TIM_SetCompare3(TIM2, servo_pwm);
			delay_ms(20);
		} 
	}  
}

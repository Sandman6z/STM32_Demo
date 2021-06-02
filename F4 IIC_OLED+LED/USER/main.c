#include "stm32f4xx.h"                  // Device header

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "myiic.h"


int main(void)
{ 
	//int i;
	delay_init(168);		  //��ʼ����ʱ����
	//LED_Init();		        //��ʼ��LED�˿�
	//OLED_GPIO_Init();
	IIC_Init();
	OLED_Init();
	/**������ͨ��ֱ�Ӳ����⺯���ķ�ʽʵ��IO����**/	
	
	while(1)
	{
		OLED_P8x16Str(0,0,"HelTec");				//��һ�� -- 8x16����ʾ��Ԫ��ʾASCII��
		OLED_P8x16Str(0,2,"OLED Display");
		OLED_P8x16Str(0,4,"www.heltec.cn");
		OLED_P6x8Str(0,6,"cn.heltec@gmail.com");
		OLED_P6x8Str(0,7,"heltec.taobao.com");
		delay_ms(1000);
			 
		//OLED_CLS();
         
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0��Ӧ����GPIOF.9���ͣ���  ��ͬLED0=0;
		GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1��Ӧ����GPIOF.10���ߣ��� ��ͬLED1=1;
		delay_ms(500);  		   //��ʱ300ms
		GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0��Ӧ����GPIOF.0���ߣ���  ��ͬLED0=1;
		GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1��Ӧ����GPIOF.10���ͣ��� ��ͬLED1=0;
		delay_ms(500);                     //��ʱ300ms
	}
}

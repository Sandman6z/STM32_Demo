#include "stm32f10x.h"                  // Device header
#include "led.h"

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

int main(void)
{
	LED_GPIO_Config();
	
	while(1)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		Delay(1000000);

		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		Delay(100000);
		Delay(100000);

		
	}
}

#include "stm32f10x.h"

void Delay(uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

int main(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);            

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	while (1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
//		Delay(0xfffff);
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);
		Delay(0xfffff);
	}
}

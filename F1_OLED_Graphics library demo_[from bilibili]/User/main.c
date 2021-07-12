#include "stm32f10x.h"
#include "delay.h"
#include "bsp_usart.h"
#include "test.h"
#include "draw_api.h"

int main(void)
{
/* 嵌套向量中断控制器组选择 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	DelayInit();
	USART_Config();
	InitGraph();	

	while(1)
	{
		demo();	
	}
}

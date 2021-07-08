#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" 

#define LED_GPIO_PIN 	GPIO_Pin_10
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_CLK 	RCC_APB2Periph_GPIOB

void LED_GPIO_Config(void);

#endif /*__LED_H*/

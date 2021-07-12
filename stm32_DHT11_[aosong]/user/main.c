#include "stm32f10x.h"
#include "ili9320.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "math.h" 
#include "AM23XX.H"
#include <stdio.h>

void SZ_STM32_SysTickInit(uint32_t HzPreSecond);
s32 temperature;
u16 humidity;
void SysTickDelay(__IO uint32_t nTime);
__IO uint32_t TimingDelay;
void SysTickDelay(__IO uint32_t nTime)
{ 
    TimingDelay = nTime;
    while(TimingDelay != 0);		
}
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PG�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PG11�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				 //��ʼ��IO��
 	GPIO_SetBits(GPIOA,GPIO_Pin_5);					//PG11 �����
	   
	//DHT11_Rst();  //��λDHT11
	printf("\r\n ׼�� %dth\r\n",11);
	//return DHT11_Check();//�ȴ�DHT11�Ļ�Ӧ
	return 0;
} 

/* �������궨�� bitband macro ------------------------------------------------*/
/* ʹ��bitband����������bit�����ĳ����Ч�ʣ�����GPIO�ܽŵĿ���Ч����Ϊ���� */
/* ��������� ��32MB����������ķ���ӳ��Ϊ��1MB ����bit-band���ķ���(ʵ�ʴ�С����оƬ�й�) */
#define Periph_BASE         0x40000000  // �������ַ Peripheral 
#define Periph_BB_BASE      0x42000000  // �������������ַ Peripheral bitband

/* ע�⣺���볣������ʱ���ڱ���ʱ��������������������ַ�������ܴﵽ����Ч�ʵ�Ŀ��(�Ƽ�)
         ����������������ֻ��������ʱ��STM32�Լ������������ַ��Ч�ʻ����ۿ�(���Ƽ�) */
#define Periph_BB(PeriphAddr, BitNumber)    \
          *(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2))
	 
#define Periph_ResetBit_BB(PeriphAddr, BitNumber)    \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define Periph_SetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Periph_GetBit_BB(PeriphAddr, BitNumber)       \
          (*(__IO uint32_t *) (Periph_BB_BASE | ((PeriphAddr - Periph_BASE) << 5) | ((BitNumber) << 2)))


/* ����GPIO����������������壬nΪbitλ�÷�ΧΪ0��15    */
/* ���Ƕ�GPIOA.15����������Ҫ��ʼ��GPIO��Ȼ��ʹ�÷����� */
/* ��GPIOA.15����͵�ƽ��   PAOutBit(15) = 0;           */
/* ��GPIOA.15����͵�ƽ��   PAOutBit(15) = 1;           */
/* ��ȡGPIOA.15����ĵ�ƽ�� data = PAInBit(15);         */
#define PAOutBit(n)     Periph_BB((uint32_t)&GPIOA->ODR,n)  //��� 
#define PASetBit(n)     (PAOutBit(n) = 1)                   //��� ��
#define PAResetBit(n)   (PAOutBit(n) = 0)                   //��� ��
#define PAInBit(n)      Periph_BB((uint32_t)&GPIOA->IDR,n)  //���� 
#define PAflowtingBit(n)  Periph_BB((uint32_t)&GPIOA->CRH,n)  //�˿ڸ���

#define PBOutBit(n)     Periph_BB((uint32_t)&GPIOB->ODR,n)  //��� 
#define PBSetBit(n)     (PBOutBit(n) = 1)                   //��� ��
#define PBResetBit(n)   (PBOutBit(n) = 0)                   //��� ��
#define PBInBit(n)      Periph_BB((uint32_t)&GPIOB->IDR,n)  //���� 

#define PCOutBit(n)     Periph_BB((uint32_t)&GPIOC->ODR,n)  //��� 
#define PCSetBit(n)     (PCOutBit(n) = 1)                   //��� ��
#define PCResetBit(n)   (PCOutBit(n) = 0)                   //��� ��
#define PCInBit(n)      Periph_BB((uint32_t)&GPIOC->IDR,n)  //���� 

#define PDOutBit(n)     Periph_BB((uint32_t)&GPIOD->ODR,n)  //��� 
#define PDSetBit(n)     (PDOutBit(n) = 1)                   //��� ��
#define PDResetBit(n)   (PDOutBit(n) = 0)                   //��� ��
#define PDInBit(n)      Periph_BB((uint32_t)&GPIOD->IDR,n)  //���� 

#define PEOutBit(n)     Periph_BB((uint32_t)&GPIOE->ODR,n)  //��� 
#define PESetBit(n)     (PEOutBit(n) = 1)                   //��� ��
#define PEResetBit(n)   (PEOutBit(n) = 0)                   //��� ��
#define PEInBit(n)      Periph_BB((uint32_t)&GPIOE->IDR,n)  //����

#define PFOutBit(n)     Periph_BB((uint32_t)&GPIOF->ODR,n)  //��� 
#define PFSetBit(n)     (PFOutBit(n) = 1)                   //��� ��
#define PFResetBit(n)   (PFOutBit(n) = 0)                   //��� ��
#define PFInBit(n)      Periph_BB((uint32_t)&GPIOF->IDR,n)  //����

#define PGOutBit(n)     Periph_BB((uint32_t)&GPIOG->ODR,n)  //��� 
#define PGSetBit(n)     (PGOutBit(n) = 1)                   //��� ��
#define PGResetBit(n)   (PGOutBit(n) = 0)                   //��� ��
#define PGInBit(n)      Periph_BB((uint32_t)&GPIOG->IDR,n)  //����


/* �ڲ�SRAM������ ��32MB SRAM�������ķ���ӳ��Ϊ��1MB SRAMbit-band���ķ���(ʵ�ʴ�С����оƬ�й�) */
#define RAM_BASE            0x20000000  // �ڲ�SRAM����ַ  
#define RAM_BB_BASE         0x22000000  // �ڲ�SRAM����������ַ

#define SRAM_ResetBit_BB(VarAddr, BitNumber)    \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)
   
#define SRAM_SetBit_BB(VarAddr, BitNumber)       \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define SRAM_GetBit_BB(VarAddr, BitNumber)       \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))

USART_InitTypeDef USART_InitStructure;

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)


#define DA_PIN_NUM                     11 /* bitband������ʹ�ú궨��  */
#define DA_PIN                         GPIO_Pin_11
#define DA_GPIO_PORT                   GPIOA
#define DA_GPIO_CLK                    RCC_APB2Periph_GPIOA  
#define DAOBB                          Periph_BB((uint32_t)&DA_GPIO_PORT->ODR, DA_PIN_NUM)
#define PA11_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=8<<12;} //��������
#define PA11_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=3<<12;} //ͨ���������  50M
////IO��������											   
#define	DHT11_DQ_IN  PAInBit(11)  //���ݶ˿�	PA11
#define PA11_0		PAResetBit(11)
#define PA11_1		PASetBit(11)
#define	PA11_INDATA 	PAInBit(11)  //���ݶ˿�	PA11

DHT11_Data_TypeDef DHT11_Data;
void SZ_STM32_SysTickInit(uint32_t HzPreSecond)
{
    if (SysTick_Config(SystemCoreClock / HzPreSecond))
    { 
        /* Capture error */ 
        while (1);
    }
}
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    { 
        TimingDelay--;
    }
}

void Delayus(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

void STM32_Shenzhou_COMInit(USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

  /* Enable UART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  USART_Init(USART1, USART_InitStruct);	/* USART configuration */
  USART_Cmd(USART1, ENABLE);  /* Enable USART */
  //USART_Cmd(USART1, DISABLE);
  
}

/**-------------------------------------------------------
  * @������ TimingDelay_Decrement
  * @����   ϵͳ���Ķ�ʱ�����������õ��Ӻ���
  *         ��ȫ�ֱ���TimingDelay��һ������ʵ����ʱ
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/

/**-------------------------------------------------------
  * @������ SysTick_Handler
  * @����   ϵͳ���Ķ�ʱ��������������
  * @����   ��
  * @����ֵ ��
***------------------------------------------------------*/
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

void NVIC_GroupConfig(void)
{
    /* ����NVIC�ж����ȼ�����:
     - 1���ر�ʾ�����ȼ�  �����ȼ��Ϸ�ȡֵΪ 0 �� 1 
     - 3���ر�ʾ�����ȼ�  �����ȼ��Ϸ�ȡֵΪ 0..7
     - ��ֵԽ�����ȼ�Խ�ߣ�ȡֵ�����Ϸ���Χʱȡ��bitλ 
    */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /*==================================================================================
      NVIC_PriorityGroup   |  �����ȼ���Χ  |  �����ȼ���Χ  |   ����
      ==================================================================================
     NVIC_PriorityGroup_0  |      0         |      0-15      |   0 ���ر�ʾ�����ȼ�
                           |                |                |   4 ���ر�ʾ�����ȼ� 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_1  |      0-1       |      0-7       |   1 ���ر�ʾ�����ȼ�
                           |                |                |   3 ���ر�ʾ�����ȼ� 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_2  |      0-3       |      0-3       |   2 ���ر�ʾ�����ȼ�
                           |                |                |   2 ���ر�ʾ�����ȼ� 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_3  |      0-7       |      0-1       |   3 ���ر�ʾ�����ȼ�
                           |                |                |   1 ���ر�ʾ�����ȼ� 
     ----------------------------------------------------------------------------------
     NVIC_PriorityGroup_4  |      0-15      |      0         |   4 ���ر�ʾ�����ȼ�
                           |                |                |   0 ���ر�ʾ�����ȼ�   
    ==================================================================================*/
}
/**-------------------------------------------------------
  * @������ SZ_STM32_SysTickInit
  * @����   ��ʼ��ϵͳ��ʱ��SysTick
  *         �û����Ը�����Ҫ�޸�
  * @����   ÿ���жϴ���
  * @����ֵ ��
***------------------------------------------------------*/

//USART_InitTypeDef USART_InitStructure;
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

//static void Delay_ARMJISHU(__IO uint32_t nCount)
//{
// // for (; nCount != 0; nCount--);
//}

void Read_Sensor()
{	// ��ȡ����������
	if( Read_DHT11(&DHT11_Data)==SUCCESS)										 //��\����ʾת��һ����
	{
		printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊʮ�����ƣ�%02x.%02x ��RH ���¶�Ϊʮ�����ƣ�%02x.%02x �� \r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);

		printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		display(DHT11_Data.tem_10,DHT11_Data.hh_10) ;
	}	  
}

int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured, 
		 this is done through SystemInit() function which is called from startup
		 file (startup_stm32f10x_xx.s) before to branch to application main.
		 To reconfigure the default setting of SystemInit() function, refer to
		 system_stm32f10x.c file
	 */     
								
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM32_Shenzhou_COMInit(&USART_InitStructure);
	SZ_STM32_SysTickInit(1000000);
	/* Output a message on Hyperterminal using printf function */
	ili9320_Initializtion();
	printf("\r\n ׼����ʼ�� %dth\r\n",11);
	/*TFT-LCD������ʾ����1*/  
	jiemian();
	DHT11_GPIO_Config(); 
		
		
		
	while(1)
	{	   
		Read_Sensor();		  // ��ȡ����������
	} 			   
}

PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);

  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

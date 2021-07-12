#include "AM23XX.h"
uint8_t a=0;
uint8_t flag11=0;
uint16_t count =0;
/*
 * ��������DHT11_GPIO_Config
 * ����  ������DHT11�õ���I/O��
 * ����  ����
 * ���  ����
 */
 void delay(int tt)
 {	   int j;
    for(;tt!=0;tt--)
		for(j=44;j>0;j--);
 }
void DHT11_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOD������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOD����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 

	/*���ÿ⺯������ʼ��GPIOD*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  

	/* ����GPIOD12	*/
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	printf("DHT11 �����꣡��");	 
	printf("\n\n");
}

/*
 * ��������DHT11_Mode_IPU
 * ����  ��ʹDHT11-DATA���ű�Ϊ����ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_IN_FLOATING(void)
{
 	  GPIO_InitTypeDef GPIO_InitStructure;

	  	/*ѡ��Ҫ���Ƶ�GPIOD����*/	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;

	   /*��������ģʽΪ��������ģʽ*/ 
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 

	  /*���ÿ⺯������ʼ��GPIOD*/
	  GPIO_Init(GPIOA, &GPIO_InitStructure);	 
}

/*
 * ��������DHT11_Mode_Out_PP
 * ����  ��ʹDHT11-DATA���ű�Ϊ���ģʽ
 * ����  ����
 * ���  ����
 */
static void DHT11_Mode_Out_PP(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*ѡ��Ҫ���Ƶ�GPIOD����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_10MHz;

	/*���ÿ⺯������ʼ��GPIOD*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);	 	 
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//void SDA_Pin_Output_High(void)
//{
//	GPIOA->DDR |= SDA_Pin;		//���ģʽ
//	GPIOA->ODR |= SDA_Pin;		//���'1'	
//	GPIOA->CR1 |= SDA_Pin;		//����ģʽ  ��©�˿ڴ�λ��Ч
//	GPIOA->CR2 |= SDA_Pin;		//�������
//}
//
//void SDA_Pin_Output_Low(void)
//{
//	GPIOA->DDR |= SDA_Pin;		 //���ģʽ
//	GPIOA->ODR &= (~SDA_Pin);		//���'0'	
//	GPIOA->CR1 |= SDA_Pin;		  //����ģʽ  ��©�˿ڴ�λ��Ч
//	GPIOA->CR2 |= SDA_Pin;		 //�������
//}
//
//void SDA_Pin_IN_FLOATING(void)
//{
//	GPIOA->CR2 &= ~(SDA_Pin);			//��ֹ�ⲿ�ж�
//	GPIOA->DDR &= ~(SDA_Pin);			//����ģʽ
//	GPIOA->CR1 &= ~(SDA_Pin);			//��������
//}
//-----------------------------------------------------------------------------------------------
static uint8_t Read_Byte(void)
{	  

   	 uint8_t i, temp=0;

	 for(i=0;i<8;i++)    
	 {
	   /*ÿbit��50us�͵�ƽ���ÿ�ʼ����ѯֱ���ӻ����� ��50us �͵�ƽ ����*/  
    	while(DHT11_DATA_IN()==Bit_RESET);//{if(++count>5000) break;};
		 
		 /*DHT11 ��27~28us�ĸߵ�ƽ��ʾ��0������70us�ߵ�ƽ��ʾ��1����
	 		 ͨ�����60us��ĵ�ƽ��������������״̬*/

		//delay(5); //��ʱ60us
		SysTickDelay(40);		   	  
	
		  if(DHT11_DATA_IN()==Bit_SET)//60us����Ϊ�ߵ�ƽ��ʾ���ݡ�1��
		   {
		   	/*��ѯֱ���ӻ�������ʣ��� 30us �ߵ�ƽ����*/
   				 while(DHT11_DATA_IN() ==Bit_SET);//{if(++count>500) break;}
				 // SysTickDelay(1);
				 temp|=(uint8_t)(0x01<<(7-i));  //�ѵ�7-iλ��1 
			
		   }
		   else	 //60us��Ϊ�͵�ƽ��ʾ���ݡ�0��
		   {//SysTickDelay(1);			   
		   	  temp&=(uint8_t)~(0x01<<(7-i)); //�ѵ�7-iλ��0
		   }
	 }
	  return temp;
}

uint8_t Read_DHT11(DHT11_Data_TypeDef *DHT11_Data)
{  

	DHT11_Mode_Out_PP();
		DHT11_DATA_OUT(HIGH);
		SysTickDelay(500000); 
	/*��������*/
	//DHT11_Mode_Out_PP();
  	DHT11_DATA_OUT(LOW);
   //*��ʱ18ms*/800US
   	SysTickDelay(2000);	//һ��Ҫ2MS ����ʼ�ź�
  //	DHT11_Mode_IN_FLOATING();
   /*�������� ������ʱ30us*/
   	//DHT11_DATA_OUT(HIGH); 
	DHT11_DATA_OUT(HIGH);
  	SysTickDelay(30);
   	/*������Ϊ���� �жϴӻ���Ӧ�ź�*/ 
   //	DHT11_Mode_IN_FLOATING();
	DHT11_Mode_IN_FLOATING();
  //delay(3);
 /*�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������*/   
  //while(DHT11_DATA_IN() ==Bit_SET){a++;if(a>10) break;}
   SysTickDelay(10);
			if(DHT11_DATA_IN()==Bit_RESET)
				{	
					  /*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/
					count =0;
					while(DHT11_DATA_IN()==Bit_RESET);// {if(++count>500) break;}
					count =0;
					while(DHT11_DATA_IN()==Bit_SET);//{if(++count>500) break;}

	  /*��ѯֱ���ӻ������� 80us �ߵ�ƽ �����źŽ���*/
	  /*��ʼ��������*/   
	 	 			DHT11_Data->humi_int= Read_Byte();	   //0
								
		 			DHT11_Data->humi_deci= Read_Byte();	  //1
				
		 			DHT11_Data->temp_int= Read_Byte();			 //2

		 			DHT11_Data->temp_deci= Read_Byte();			//3
				 		
		 			DHT11_Data->check_sum= Read_Byte();
		 								  
		 delay(1);
		 	/*��ȡ���������Ÿ�Ϊ���ģʽ*/
  		 DHT11_Mode_Out_PP();
		   /*��������*/
		 DHT11_DATA_OUT(HIGH);
		 DHT11_Data->check_sum_tep=DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci;
		   /*����ȡ�������Ƿ���ȷ*/
		 if(DHT11_Data->check_sum == DHT11_Data->check_sum_tep)
		  	{
			//	display(DHT11_Data->temp_int,DHT11_Data->humi_int) ;
			//	delay(200000);
			//	display(DHT11_Data->temp_deci,DHT11_Data->humi_deci) ;
			//	delay(200000);
			/* AM23XX �������********/
				DHT11_Data->hh = DHT11_Data->humi_int;
				DHT11_Data->hh <<= 8;
				DHT11_Data->hh |= DHT11_Data->humi_deci;
				if(0>DHT11_Data->hh||DHT11_Data->hh>=1000)DHT11_Data->hh=999;
				

				DHT11_Data->tem = DHT11_Data->temp_int;
				DHT11_Data->tem <<= 8;
				DHT11_Data->tem |= DHT11_Data->temp_deci;
				if(0>DHT11_Data->tem||DHT11_Data->tem>=1000)DHT11_Data->tem=999;


				DHT11_Data->hh_10=DHT11_Data->hh/10;
				DHT11_Data->tem_10 =DHT11_Data->tem/10;


				return SUCCESS;

			}
		  else 
		  	{
		//	printf("��ֵ�����\n");
			return ERROR;
			}
   }
   else
   	{		
			return ERROR;
		}
   			 	
}

	  


/*************************************END OF FILE******************************/

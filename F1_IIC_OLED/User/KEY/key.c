#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "delay.h"

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTE,PORTE��PORTAʱ��

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������

u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;//������־
    if(mode)key_up = 1;  //֧������
    //��ⰴ���Ƿ���
    if(key_up&&(Upper_KEY==0||Left_KEY==0||Right_KEY==0||Lower_KEY==0||Determine_KEY==0||Return_KEY==0))
    {
        delay_ms(10);//ȥ����
        key_up = 0;
        if		 (Upper_KEY     == 0)           return Upper;
        else if(Left_KEY      == 0)           return Left;
        else if(Right_KEY     == 0)           return Right;
        else if(Lower_KEY     == 0)           return Lower;
        else if(Determine_KEY == 0)           return Determine;
        else if(Return_KEY    == 0)           return Return;

    }
    //��ⰴ���Ƿ��ɿ�
    else if(Upper_KEY==1 && Left_KEY==1 && Right_KEY==1 && Lower_KEY==1 && Determine_KEY==1 && Return_KEY==1)
        key_up = 1;
    return 0;//�ް�������
}

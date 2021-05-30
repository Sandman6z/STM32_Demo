#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "delay.h"

//按键初始化函数
void KEY_Init(void) //IO初始化
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTE,PORTE，PORTA时钟

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下

u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;//按键标志
    if(mode)key_up = 1;  //支持连按
    //检测按键是否按下
    if(key_up&&(Upper_KEY==0||Left_KEY==0||Right_KEY==0||Lower_KEY==0||Determine_KEY==0||Return_KEY==0))
    {
        delay_ms(10);//去抖动
        key_up = 0;
        if		 (Upper_KEY     == 0)           return Upper;
        else if(Left_KEY      == 0)           return Left;
        else if(Right_KEY     == 0)           return Right;
        else if(Lower_KEY     == 0)           return Lower;
        else if(Determine_KEY == 0)           return Determine;
        else if(Return_KEY    == 0)           return Return;

    }
    //检测按键是否松开
    else if(Upper_KEY==1 && Left_KEY==1 && Right_KEY==1 && Lower_KEY==1 && Determine_KEY==1 && Return_KEY==1)
        key_up = 1;
    return 0;//无按键按下
}

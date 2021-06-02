#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

//#define Upper_KEY      PBin(6)
//#define Left_KEY       PBin(7)
//#define Right_KEY      PBin(8)
//#define Lower_KEY      PBin(9)
//#define Determine_KEY  PCin(13)
//#define Return_KEY     PCin(14)
/*************************************change for test*/
#define Upper_KEY      PCin(1)
#define Left_KEY       PBin(7)
#define Right_KEY      PBin(8)
#define Lower_KEY      PCin(13)
#define Determine_KEY  PBin(6)
#define Return_KEY     PBin(9)
/***************************************************/
#define ALL (key==Upper||key==Left||key==Right||key==Lower||key==Determine||key==Return)

//#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
//#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
//#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP)

#define Upper      2  //上
#define Left       3  //左
#define Right      4  //右 
#define Lower      5  //下
#define Determine  6  //确定
#define Return     7  //返回

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数
#endif

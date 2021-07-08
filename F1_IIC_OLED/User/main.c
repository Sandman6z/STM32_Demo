#include "sys.h"
#include "lnterface.h"
#include "bmp.h"

int year=2018,month=4,day=12;//年月日
int time=13,branch=10,second=00;//时分秒
u8 key=0;
int Choice=2;
int Bluetooth_Sign=1,WIFI_Sign=33,Flashlight_Sign=1,Electricity_Sign=4;
int Status_Bar_Sgin=0,Content_Column_Sgin=0;
int Key_Selectio=0;
int conu=0;
int Page_Sgin=0;
int count=0;
int Return_Sgin=0;
int Sgin=1;

//JTAG模式设置,用于设置JTAG的模式
//mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00
void JTAG_Set(u8 mode)
{
    u32 temp;
    temp = mode;
    temp<<=25;
    RCC->APB2ENR |= 1<<0;     //开启辅助时钟
    AFIO->MAPR &= 0XF8FFFFFF; //清除MAPR的[26:24]
    AFIO->MAPR |= temp;       //设置jtag模式
}

int main(void)
{
    delay_init();
    JTAG_Set(JTAG_SWD_DISABLE);
    JTAG_Set(SWD_ENABLE);
    uart_init(9600);
    IIC_Init();
    OLED_Init();
    LED_Init();
    KEY_Init();
    while(1)
    {
//		OLED_P16x32Ch(1*16,2,1);
//		OLED_P16x32Ch(2*16,2,2);
//		OLED_P16x32Ch(3*16,2,10);
//		OLED_P16x32Ch(4*16,2,2);
//		OLED_P16x32Ch(5*16,2,8);
//		OLED_P32x32Ch(1*32,2,0);
//		OLED_P32x32Ch(2*32,2,1);
//		OLED_P128x48Ch(0,2,0);
			Status_Bar();
			OLED_P8x16Str(1*16,2,"MCU");            
			OLED_P8x16Str(1*16,4,"QQ");             
			OLED_P8x16Str(1*16,6,"20212333");             
			OLED_P16x16Ch(0*16,Choice,44);          //选择
//	OLED_P16x16Ch(1*16,2,65);                 //蓝
//	OLED_P16x16Ch(2*16,2,66);                 //牙
//
//	OLED_P8x16Str(1*16,4,"WIFI");             //WIFI
//
//	OLED_P16x16Ch(1*16,6,67);                   //温
//	OLED_P16x16Ch(2*16,6,68);                   //度
//
//	OLED_ShowNum(6*16,6,Choice/2,1,12);
//	OLED_P6x8Str(6.5*16,7,"/");
//	OLED_P6x8Str(7*16,7,"10");
    }
}

#include "includes.h"

#define LED_FICKER_LIB  1 //灯闪烁开
//static void Delay(u32 i);
/****************************************************
函数名：GPIO_LED_Init
形参：无
返回值：无
函数功能：对4个LED灯进行初始化,并让灯闪烁一下，检测灯是否有坏
****************************************************/
void GPIO_LED_Init(void)
{
#ifdef LED_FICKER_LIB

	GPIO_InitTypeDef GPIO_InitStructure;
	//对GPIOB口的时钟打开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	//把IO口配置为输出模式
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//设置管脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//pb5 输出模式 50MHZ
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
#else

	RCC->APB2ENR|=(1<<2)|(1<<3)|(1<<6);    		//使能PORTA、PORTB、PORTE时钟	 
	
	GPIOA->CRL&=~((0x0f<<(4*5))|(0x0f<<(4*6)));
	GPIOA->CRL|=(0x03<<(4*5))|(0x03<<(4*6));	//PA.5、PA6推挽输出,50HZ
	GPIOA->ODR|=(1<<5)|(1<<6);      					//PA.5、PA6输出高 	(灭灯)
	   	 
	GPIOB->CRL &=~(0x0f<<(4*5)); 
	GPIOB->CRL |=0x03<<(4*5);									//PB.5 推挽输出  50HZ 	 
	GPIOB->ODR |=1<<5;      									//PB.5 输出高（灭灯）
											  
	GPIOE->CRL&=~(0x0f<<(4*5));
	GPIOE->CRL|=0x03<<(4*5);									//PE.5推挽输出   50HZ
	GPIOE->ODR|=1<<5;      										//PE.5输出高（灭灯）
	
#endif

}
/****************************************************
函数名：LED_SetAll
形参：无
返回值：无
函数功能：点亮所有的灯
****************************************************/
void LED_SetAll(void)
{
	LED1(1);
	LED2(1);
	LED3(1);
	LED4(1);
}
/****************************************************
函数名：LED_ClearAll
形参：无
返回值：无
函数功能：熄灭所有的灯
****************************************************/
void LED_ClearAll(void)
{
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);
}
/****************************************************
函数名：Delay
形参：i 代表的是要延迟的时间长度
返回值：无
函数功能：延迟函数
****************************************************/
//static void Delay(u32 i)
//{
//	for(;i>0;i--);
//}
/****************************************************
函数名：Flashing_Light
形参：  无
返回值：无
函数功能：点灯程序1、全亮全灭  2、流水灯(寄存器版)
****************************************************/
//#ifdef LED_FICKER_LIB
void Flashing_Light(void)
{

		LED_SetAll();//灯全亮
		delay_nms(500);//延时500ms
		LED_ClearAll();//灯全灭
		delay_nms(500);
}
//#else
//void Flashing_Light(void)
//{			
//		
//		GPIOA->ODR&=~(0x01<<6);//LED4(1);
//		delay_nms(100);
//		GPIOA->ODR&=~(0x01<<5);//LED3(1);
//		delay_nms(100);	
//		GPIOE->ODR&=~(0x01<<5);//LED2(1);
//		delay_nms(100);
//		GPIOB->ODR&=~(0x01<<5);//LED1(1);
//		delay_nms(100);
//		GPIOA->ODR|=0x01<<5;	//LED1(0);
//		GPIOA->ODR|=0x01<<6;	//LED2(0);
//		GPIOB->ODR|=0x01<<5;	//LED3(0);
//		GPIOE->ODR|=0x01<<5;  //LED4(0);
//		delay_nms(100);
//}
//#endif




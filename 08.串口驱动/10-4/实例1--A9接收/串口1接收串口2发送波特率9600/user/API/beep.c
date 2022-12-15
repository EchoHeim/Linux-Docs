#include "includes.h"



/****************************************************
函数名：GPIO_LED_Init
形参：无
返回值：无
函数功能：蜂鸣器初始化
****************************************************/
void GPIO_BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//对GPIOB口的时钟打开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//把IO口配置为输出模式
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//设置管脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

/****************************************************
函数名：LED_SetAll
形参：无
返回值：无
函数功能：蜂鸣器开
****************************************************/
void BEEP_ON(void)
{
	BEEP(0);
}

/****************************************************
函数名：LED_SetAll
形参：无
返回值：无
函数功能：蜂鸣器关
****************************************************/
void BEEP_OFF(void)
{
	BEEP(1);
}

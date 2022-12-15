#include "includes.h"

KEY_Type Key_Switch;

/****************************************************
函数名：Delay
形参：i 代表的是要延迟的时间长度
返回值：无
函数功能：延迟函数
****************************************************/
static void Delay(u32 i)
{
	for(;i>0;i--);
}

/****************************************************
函数名：GPIO_KEY_Init
形参：无
返回值：无
函数功能：4个按键的初始化
****************************************************/
void GPIO_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	//按键都是输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
}
/****************************************************
函数名：Get_Key
形参：无
返回值：返回按键值
函数功能：读IO口状态，返回按键值
****************************************************/
u8 Get_Key(void)
{
	if(!KEY1() || !KEY2() || !KEY3() || KEY4())//判断按键是否按下
	{
		Delay(50000);
		if(!KEY1() || !KEY2() || !KEY3() || KEY4())//消抖
		{
			if(!KEY1())
			{
				while(!KEY1());//松手检测
				return Key_Up;
			}
			else if(!KEY2())
			{
				while(!KEY2());
				return Key_Right;
			}
			else if(!KEY3())
			{
				while(!KEY2());
				return Key_Down;
			}
			else if(KEY4())
			{
				while(KEY4());
				return Key_Left;
			}
		}
	}
	return Key_None;
}

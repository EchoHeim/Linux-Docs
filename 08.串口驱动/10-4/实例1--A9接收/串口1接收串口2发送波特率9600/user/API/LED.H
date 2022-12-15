#ifndef _LED_H_
#define _LED_H_
#include "stm32f10x.h"

#define LED1(x) x?GPIO_ResetBits(GPIOB,GPIO_Pin_5): GPIO_SetBits(GPIOB,GPIO_Pin_5)  //根据x，来让管脚B-5，输出0或者1
#define LED2(x) x?GPIO_ResetBits(GPIOE,GPIO_Pin_5): GPIO_SetBits(GPIOE,GPIO_Pin_5)  //根据x，来让管脚E-5，输出0或者1
#define LED3(x) x?GPIO_ResetBits(GPIOA,GPIO_Pin_5): GPIO_SetBits(GPIOA,GPIO_Pin_5)  //根据x，来让管脚A-5，输出0或者1
#define LED4(x) x?GPIO_ResetBits(GPIOA,GPIO_Pin_6): GPIO_SetBits(GPIOA,GPIO_Pin_6)  //根据x，来让管脚A-6，输出0或者1
				 
				  
extern void GPIO_LED_Init(void);  //LED灯初始化函数
void LED_SetAll(void);     //点亮所有的LED灯
void LED_ClearAll(void);   //熄灭所有的LED灯 
void Flashing_Light(void); //灯闪烁
#endif

#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

#define KEY1() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) //��A-0�ܽŵ�״̬
#define KEY2() GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //��E-4�ܽŵ�״̬
#define KEY3() GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) //��E-3�ܽŵ�״̬
#define KEY4() GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //��E-2�ܽŵ�״̬

typedef enum                                         //ö�ٰ�����״̬
{
	Key_None = 0,Key_Up = 1,Key_Down,Key_Left,Key_Right
}KEY_Type;

extern KEY_Type Key_Switch;                          //����һ��ö�ٱ���
void GPIO_KEY_Init(void);                            //�����ĳ�ʼ��
u8 Get_Key(void);   								 //��ð���ֵ

#endif


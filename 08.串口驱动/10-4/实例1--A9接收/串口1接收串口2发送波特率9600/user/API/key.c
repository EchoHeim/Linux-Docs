#include "includes.h"

KEY_Type Key_Switch;

/****************************************************
��������Delay
�βΣ�i �������Ҫ�ӳٵ�ʱ�䳤��
����ֵ����
�������ܣ��ӳٺ���
****************************************************/
static void Delay(u32 i)
{
	for(;i>0;i--);
}

/****************************************************
��������GPIO_KEY_Init
�βΣ���
����ֵ����
�������ܣ�4�������ĳ�ʼ��
****************************************************/
void GPIO_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	//������������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
}
/****************************************************
��������Get_Key
�βΣ���
����ֵ�����ذ���ֵ
�������ܣ���IO��״̬�����ذ���ֵ
****************************************************/
u8 Get_Key(void)
{
	if(!KEY1() || !KEY2() || !KEY3() || KEY4())//�жϰ����Ƿ���
	{
		Delay(50000);
		if(!KEY1() || !KEY2() || !KEY3() || KEY4())//����
		{
			if(!KEY1())
			{
				while(!KEY1());//���ּ��
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

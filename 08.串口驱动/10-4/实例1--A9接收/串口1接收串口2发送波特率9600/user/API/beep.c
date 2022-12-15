#include "includes.h"



/****************************************************
��������GPIO_LED_Init
�βΣ���
����ֵ����
�������ܣ���������ʼ��
****************************************************/
void GPIO_BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//��GPIOB�ڵ�ʱ�Ӵ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//��IO������Ϊ���ģʽ
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//���ùܽ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

/****************************************************
��������LED_SetAll
�βΣ���
����ֵ����
�������ܣ���������
****************************************************/
void BEEP_ON(void)
{
	BEEP(0);
}

/****************************************************
��������LED_SetAll
�βΣ���
����ֵ����
�������ܣ���������
****************************************************/
void BEEP_OFF(void)
{
	BEEP(1);
}
